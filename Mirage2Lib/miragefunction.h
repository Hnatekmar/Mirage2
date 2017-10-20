#ifndef MIRAGEFUNCTION_H
#define MIRAGEFUNCTION_H

#include "value.h"
#include <memory>

class MirageFunction {
public:
    virtual MirageValue call(LinkedList<MirageValue> args) = 0;
};

Q_DECLARE_METATYPE(std::shared_ptr<MirageFunction>)

#endif // MIRAGEFUNCTION_H
