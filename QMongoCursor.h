#ifndef QMONGOCURSOR_H
#define QMONGOCURSOR_H

#include <QObject>
#include <QVariant>
#include <mongo/client/dbclient.h>

class QMongoCursor : public QObject
{
    Q_OBJECT
public:
    explicit QMongoCursor(mongo::DBClientCursor* cursor, QObject *parent = 0);

    Q_INVOKABLE
    bool hasNext();

    Q_INVOKABLE
    QVariantMap next();

    Q_INVOKABLE
    QVariantList toList();

    ~QMongoCursor();
signals:

public slots:

protected:
    mongo::DBClientCursor* cursor() { Q_ASSERT(m_cursor); return m_cursor; }
    mongo::DBClientCursor* m_cursor;

};

#endif // QMONGOCURSOR_H
