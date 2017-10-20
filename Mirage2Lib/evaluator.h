#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <QMap>
#include "value.h"

typedef QMap<QString, MirageValue> Context;
class Evaluator
{
    Context m_context;
public:
    Evaluator(Context context);
    void setSymbol(QString key, MirageValue value) {
        m_context[key] = value;
    }
    MirageValue eval(const MirageValue& value);
};

#endif // EVALUATOR_H
