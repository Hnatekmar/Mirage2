#include "evaluator.h"
#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "plus.h"

int main()
{
    QQueue<Token> tokens = lexer("(+ 1 5)");
    LinkedList<MirageValue> list;
    program(tokens, list);
    Evaluator evaluator({
                            {"+",
                             MirageValue{
                                 QVariant::fromValue(std::shared_ptr<MirageFunction>(new Plus())),
                                 ValueType::function,
                                 false,
                                 false,
                                 false
                             }}
                        });
    while(!list.empty()) {
        qDebug() << evaluator.eval(list.first()).toString() << '\n';
        list = list.rest();
    }
    return 0;
}
