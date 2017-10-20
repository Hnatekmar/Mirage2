#include "function.h"

Function::Function(LinkedList<MirageValue> functionDefinition, Evaluator evaluator): m_evaluator(evaluator), m_args(), m_body() {
    MirageValue args = functionDefinition.first();
    if(args.type != ValueType::list) {
        throw MirageException("First argument to form function has to be list of identifiers");
    }
    m_args = args.value.value<LinkedList<MirageValue>>();
    m_body = functionDefinition.rest().rest();
}

MirageValue Function::call(LinkedList<MirageValue> args) {
    auto argIt = m_args;
    auto valIt = args;
    while(!argIt.empty()) {
        m_evaluator.setSymbol(argIt.first().value.toString(), valIt.first());
        argIt = argIt.rest();
        valIt = valIt.rest();
    }
    auto it = m_body;
    while(!it.rest().empty()) {
        m_evaluator.eval(it.first());
        it = it.rest();
    }
    return m_evaluator.eval(it.first());
}
