#include "parser.h"
#include <QQueue>
#include <QList>
#include <iostream>
#include <QDebug>


QDebug operator<<(QDebug debug, const Token &token) {
   QDebugStateSaver saver(debug);
   debug << "Token [" << token.line << "]: " << token.value;
   return debug;
}

void expression(QQueue<Token>& tokens, QList<MirageValue>& values);

/**
  Grammar:
    Program -> Expression Program | EPSILON
    Expression -> List | atom | ' Expression | ` QuasiExpression
    QuasiExpression -> ~ atom | ~@ atom | QuasiList | Expression
    QuasiList -> ( QuasiValues )
    List -> ( Values )
    Values -> Expression Values | EPSILON
    QuasiValues -> QuasiExpression Values | EPSILON
**/
inline bool isAtom(const Token& token) {
    return token.type == TokenType::identifier ||
           token.type == TokenType::number ||
           token.type == TokenType::string;
}
void error(const Token& token, const QString& errorMessage) {
    qDebug() << "Parser error: " << errorMessage << '\n';
    qDebug() << token << '\n';
    std::exit(1);
}

void quasiExpression(QQueue<Token>& tokens, QList<MirageValue>& values) {
    Token token = tokens.first();
    if(token.type == TokenType::eval) {
        tokens.pop_front();
        expression(tokens, values);
        values.last().quasiEval = true;
    } else if(token.type == TokenType::unrollEval) {
        tokens.pop_front();
        expression(tokens, values);
        values.last().quasiExpand = true;
    } else if(isAtom(token) ||
              token.type == TokenType::quote ||
              token.type == TokenType::quasiQuote ||
              token.type == TokenType::lParen){
        expression(tokens, values);
    } else {
        error(token,
              "Rule: quasiExpression\n"
              "Expected one of: atom, ', `, (, ~@, ~");
    }
}

void quasiValues(QQueue<Token>& tokens, QList<MirageValue>& values) {
    QList<MirageValue> listValues;
    Token token;
    do{
        token = tokens.first();
        if(token.type == TokenType::rParen) break;
        quasiExpression(tokens, listValues);
    } while(isAtom(token) ||
            token.type == TokenType::quote ||
            token.type == TokenType::quasiQuote ||
            token.type == TokenType::lParen ||
            token.type == TokenType::eval ||
            token.type == TokenType::unrollEval);
    values.push_back(MirageValue {
                         QVariant::fromValue(listValues),
                         ValueType::list,
                         false,
                         false,
                         false,
                         true
                     });
}

void valuesRule(QQueue<Token>& tokens, QList<MirageValue>& values) {
    QList<MirageValue> listValues;
    Token token;
    do{
        token = tokens.first();
        if(token.type == TokenType::rParen) break;
        expression(tokens, listValues);
    } while(isAtom(token) ||
            token.type == TokenType::quote ||
            token.type == TokenType::quasiQuote ||
            token.type == TokenType::lParen);
    values.push_back(MirageValue {
                         QVariant::fromValue(listValues),
                         ValueType::list,
                         false,
                         false,
                         false
                     });
}

void quasiList(QQueue<Token>& tokens, QList<MirageValue>& values) {
    Token token = tokens.first();
    if(token.type == TokenType::lParen) {
        tokens.pop_front();
        quasiValues(tokens, values);
        token = tokens.first();
        if(token.type == TokenType::rParen) {
            tokens.pop_front();
        } else {
            error(token,
                  "Rule: list"
                  "expected one of: )");
        }
    } else {
        error(token,
              "Rule: quasiList"
              "expected one of: (\n");
    }
}

void list(QQueue<Token>& tokens, QList<MirageValue>& values) {
    Token token = tokens.first();
    if(token.type == TokenType::lParen) {
        tokens.pop_front();
        valuesRule(tokens, values);
        token = tokens.first();
        if(token.type == TokenType::rParen) {
            tokens.pop_front();
        } else {
            error(token,
                  "Rule: list"
                  "expected one of: )");
        }
    } else {
        error(token,
              "Rule: list"
              "expected one of: (\n");
    }
}

void expression(QQueue<Token>& tokens, QList<MirageValue>& values) {
    Q_ASSERT(tokens.size() != 0);
    const Token& token = tokens.first();
    if(token.type == TokenType::lParen) {
       list(tokens, values);
    } else if(isAtom(token)) {
        if(token.type == TokenType::number) {
            values.push_back(MirageValue {
                                      token.value,
                                      ValueType::number,
                                      false,
                                      false,
                                      false
                      });
        } else if(token.type == TokenType::string) {
            values.push_back(MirageValue {
                                 token.value,
                                 ValueType::string,
                                 false,
                                 false,
                                 false
                             });
        } else if(token.type == TokenType::identifier) {
            values.push_back(MirageValue {
                                 token.value,
                                 ValueType::identifier,
                                 false,
                                 false,
                                 false
                             });
        }
        tokens.pop_front();
    } else if(token.type == TokenType::quote) {
        tokens.pop_front();
        expression(tokens, values);
        values.last().quoted = true;
    } else if(token.type == TokenType::quasiQuote) {
        tokens.pop_front();
        quasiList(tokens, values);
    } else {
        error(token,
              "Rule: Expression\n"
              "Expected one of: (, atom, ', `\n");
    }
}

QList<MirageValue> program(QQueue<Token> &tokens, QList<MirageValue>& values) {
    Q_ASSERT(tokens.size() != 0);
    const Token& token = tokens.first();
    if(isAtom(token) ||
       token.type == TokenType::quasiQuote ||
       token.type == TokenType::quote ||
       token.type == TokenType::lParen) {
        expression(tokens, values);
        return program(tokens, values);
    } else if (token.type == TokenType::eof) {
        return values;
    } else {
        error(token,
              "Rule: Program\n"
              "Expected one of: `, ', (, atom, $\n");
    }
    // Dead code to satisfy compiler
    return values;
}
