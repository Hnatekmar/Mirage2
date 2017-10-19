#ifndef MIRAGEEXCEPTION_H
#define MIRAGEEXCEPTION_H

#include <QString>

class MirageException {
    QString m_message;
public:
        MirageException(QString message);

        const QString& what() const {
            return m_message;
        }
};

#endif // MIRAGEEXCEPTION_H
