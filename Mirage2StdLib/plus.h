#ifndef PLUS_H
#define PLUS_H

#include "miragefunction.h"

class Plus: public MirageFunction
{
public:

    // MirageFunction interface
public:
    virtual MirageValue call(LinkedList<MirageValue> args) override;
    virtual ~Plus(){}
};

#endif // PLUS_H
