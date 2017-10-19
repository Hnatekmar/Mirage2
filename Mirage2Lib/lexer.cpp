#include "lexer.h"

QQueue<Token> lexer(QString source)
{
    enum class State {
        start,
        identifier, // [^"0-9()'~][^\s]*
        string, // ".*"
        number, // [0-9]+
        lParen, // (
        rParen, // )
        unrollEval, // ~@
        eof
    };
    #define next_char() i++
    QQueue<Token> tokens;
    int i = 0;
    QString value = "";
    unsigned long lineNumber = 0;
    auto state = State::start;
    while(i != source.size()) {
        auto current = source[i];
        if(state == State::start) {
            // [^"0-9()'~]
            if(!current.isSpace() && !current.isDigit() && current != '~'
               && current != '\'' && current != '(' && current != ')'
               && current != '`'
                && current != '"') {
                value += current;
                state = State::identifier;
                next_char();
            } else if (current.isDigit()) {
                value += current;
                state = State::number;
                next_char();
            } else if (current == '(') {
                tokens.enqueue(Token{
                                  {current},
                                  lineNumber,
                                  TokenType::lParen
                              });
                next_char();
            } else if (current == ')') {
                tokens.enqueue(Token{
                                  {current},
                                  lineNumber,
                                  TokenType::rParen
                              });
                next_char();
            } else if (current == '"') {
                state = State::string;
                next_char();
            } else if (current == '~') {
                state = State::unrollEval;
                value = current;
                next_char();
            } else if (current == '\'') {
                value = current;
                tokens.enqueue(Token {
                                   value,
                                   lineNumber,
                                   TokenType::quote
                               });
                next_char();
                value = "";
            } else if (current == '`') {
                value = current;
                tokens.enqueue(Token {
                                   value,
                                   lineNumber,
                                   TokenType::quasiQuote
                               });
                next_char();
                value = "";
            }
        } else if(state == State::number) {
            if(current.isDigit()){
                value += current;
                next_char();
            }
            else {
                state = State::start;
                tokens.enqueue(Token{
                                value.toLongLong(),
                                lineNumber,
                                TokenType::number
                              });
                value = "";
            }
        } else if(state == State::string) {
            if(current == '"') {
                state = State::start;
                tokens.enqueue(Token{
                                   value,
                                   lineNumber,
                                   TokenType::string
                               });
                value = "";
            } else {
                value += current;
            }
            next_char();
        } else if(state == State::unrollEval) {
            if(current == '@') {
                value += current;
                tokens.enqueue(Token {
                                   value,
                                   lineNumber,
                                   TokenType::unrollEval
                               });
                next_char();
            } else {
                tokens.enqueue(Token {
                                   value,
                                   lineNumber,
                                   TokenType::eval
                               });
            }
            value = "";
            state = State::start;
        } else if(state == State::identifier) {
            if(!current.isSpace() && current != '\'' && current != '(' && current != ')'
                        && current != '"') {
                value += current;
                next_char();
            } else {
                state = State::start;
                tokens.enqueue(Token {
                                   value,
                                   lineNumber,
                                   TokenType::identifier
                               });
                value = "";
            }
        }
        if(current.isSpace()) {
            if(current == QChar::LineSeparator) lineNumber++;
            next_char();
            continue;
        }
    }
    tokens.enqueue(Token{
                      "",
                      lineNumber,
                      TokenType::eof
                  });
    return tokens;
}
