#ifndef LEXER_H
#define LEXER_H

#include <QQueue>
#include "token.h"

QQueue<Token> lexer(QString source);

#endif // LEXER_H
