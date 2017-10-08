#ifndef VALUE_H
#define VALUE_H
#include <QVariant>

enum class ValueType {
    number,
    string,
    identifier,
    list
};

struct MirageValue {
   QVariant value;
   ValueType type;
   bool quoted = false;
   bool quasiEval = false;
   bool quasiExpand = false;
   bool quasiList = false;
};

Q_DECLARE_METATYPE(MirageValue);

#endif // VALUE_H
