#ifndef TOKEN_H
#define TOKEN_H

#include <QVariant>
enum class TokenType {
    identifier, // [^"0-9()'~][^\s]*
    string, // ".*"
    number, // [0-9]+
    lParen, // (
    rParen, // )
    quote, // '
    eval, // ~
    unrollEval, // ~@
    quasiQuote, // `
    eof
};

struct Token {
    QVariant value;
    unsigned long line;
    TokenType type;
    bool operator==(const Token& rhs) {
        return value == rhs.value && type == rhs.type;
    }
};

#endif // TOKEN_H
