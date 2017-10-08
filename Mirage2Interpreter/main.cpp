#include <iostream>
#include "lexer.h"
#include "parser.h"

int main()
{
    QQueue<Token> tokens = lexer("( + 1 68 'foo `(~f ~@(list '+ 12)))");
    QList<MirageValue> list;
    program(tokens, list);
    return 0;
}
