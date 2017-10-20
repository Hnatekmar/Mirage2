#ifndef FUNCTION_H
#define FUNCTION_H

#include "miragefunction.h"
#include "evaluator.h"

class Function: public MirageFunction {
    Evaluator m_evaluator;
    LinkedList<MirageValue> m_args;
    LinkedList<MirageValue> m_body;
public:
    Function(LinkedList<MirageValue> functionDefinition, Evaluator evaluator);
    MirageValue call(LinkedList<MirageValue> args) override;
};

#endif // FUNCTION_H
