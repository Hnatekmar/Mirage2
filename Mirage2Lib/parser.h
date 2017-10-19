#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "value.h"
#include <QVariant>

QList<MirageValue> program(QQueue<Token>& tokens, QList<MirageValue> &values);

#endif // PARSER_H
