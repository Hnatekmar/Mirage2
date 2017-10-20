#include "evaluator.h"
#include "miragefunction.h"
#include "function.h"

Evaluator::Evaluator(Context context): m_context(context) {
}

MirageValue Evaluator::eval(const MirageValue &value) {
    if(value.quoted) {
        return value;
    } else if(value.type == ValueType::number
              || value.type == ValueType::string
              || value.type == ValueType::function
              || value.type == ValueType::macro) {
        return value;
    } else if(value.type == ValueType::identifier) {
        return eval(m_context[value.value.toString()]);
    } else if(value.type == ValueType::list) {
        if(value.quasiList) {
            // return QuasiEval(value);
        } else {
            LinkedList<MirageValue> list = value.value.value<LinkedList<MirageValue>>();
            if(list.count() == 0) {
                throw MirageException("Attemped to eval empty list!");
            }

            auto first = list.first();
            if(first.value.toString() == "function") {
                return MirageValue {
                                    QVariant::fromValue(std::shared_ptr<MirageFunction>(new Function(list.rest(), *this))),
                                    ValueType::function,
                                    false,
                                    false,
                                    false
                };
            }
            first = eval(first);
            if(first.type != ValueType::function && first.type != ValueType::macro) {
                throw MirageException("Value is not function or macro!");
            }
            std::shared_ptr<MirageFunction> fn = first.value.value<std::shared_ptr<MirageFunction>>();
            if(first.type == ValueType::function) {
                    return fn->call(list
                                    .rest()
                                    .map([&](const MirageValue& x){ return eval(x); }));
            } else if(first.type == ValueType::macro) {
                    return eval(fn->call(list.rest()));
            }
        }
    }
}

