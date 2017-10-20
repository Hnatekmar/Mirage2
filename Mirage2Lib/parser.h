#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "value.h"
#include <QVariant>

LinkedList<MirageValue> program(QQueue<Token>& tokens, LinkedList<MirageValue> &values);

#endif // PARSER_H
