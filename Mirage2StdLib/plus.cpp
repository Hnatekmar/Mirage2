#include "plus.h"


MirageValue Plus::call(LinkedList<MirageValue> args) {
    long long number = 0;
    auto it = args;
    while(!it.empty()) {
        if(it.first().type == ValueType::number) {
            number += it.first().value.toLongLong();
        } else {
            throw MirageException("Argument to + is not a number");
        }
        it = it.rest();
    }
    return MirageValue{
        number,
        ValueType::number,
                false,
                false,
                false
    };
}
