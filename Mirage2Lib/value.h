#ifndef VALUE_H
#define VALUE_H
#include <QTextStream>
#include <QVariant>
#include "linkedlist.h"

enum class ValueType {
    number,
    string,
    identifier,
    list,
    function,
    macro
};

struct MirageValue {
   QVariant value;
   ValueType type;
   bool quoted = false;
   bool quasiEval = false;
   bool quasiExpand = false;
   bool quasiList = false;
   QString toString() {
       QString stream;
       if(type != ValueType::list) {
           if(type == ValueType::identifier || type == ValueType::string) {
               stream.append(value.toString());
           } else if(type == ValueType::number) {
               stream.append(value.toString());
           }
       } else {
           LinkedList<MirageValue> list = value.value<LinkedList<MirageValue>>();
           stream.append('(');
           while(!list.empty()) {
               stream.append(list.first().toString());
               list = list.rest();
               if(!list.empty()) stream.append(' ');
           }
           stream.append(')');
       }
       return stream;
   }
};


Q_DECLARE_METATYPE(LinkedList<MirageValue>);
Q_DECLARE_METATYPE(MirageValue);

#endif // VALUE_H
