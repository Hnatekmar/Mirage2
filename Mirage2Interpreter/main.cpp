#include <iostream>
#include "lexer.h"

int main()
{
    QQueue<Token> tokens = lexer("(12 \"test\" ' ~ ~@)");
    return 0;
}
