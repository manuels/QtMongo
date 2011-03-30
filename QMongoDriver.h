#ifndef QMONGODRIVER_H
#define QMONGODRIVER_H

#include <QObject>
#include <QVariant>
#include <QDeclarativeEngine>
#include <mongo/client/dbclient.h>

#include "QMongoType.h"
#include "QMongoCursor.h"

class QMongoDriver : public QObject
{
    Q_OBJECT
public:
    explicit QMongoDriver(QObject *parent = 0);

    Q_INVOKABLE
    QMongoDriver* init(QString host);

    Q_INVOKABLE
    QMongoCursor* find(QString ns,
              QVariantMap query,
              QVariantMap fields,
              int limit,
              int skip,
              int batchSize,
              int options);

    Q_INVOKABLE
    void insert(QString ns, QVariantMap object);

    Q_INVOKABLE
    void remove(QString ns, QVariantMap object, bool justOne);

    Q_INVOKABLE
    void update(QString ns, QVariantMap query, QVariantMap object, bool upsert, bool multi);

    Q_INVOKABLE
    QVariantMap mapReduce(QString ns, QString map, QString reduce, QVariantMap query, QString output);

    Q_INVOKABLE
    QMongoType* createObjectId(QVariantMap objId);

    Q_INVOKABLE
    QMongoType* createFunction(QString code, QVariantMap scope);

signals:

public slots:

protected:
    QDeclarativeEngine* engine() { return m_engine; }
    mongo::DBClientConnection* conn() { return m_c; }

    QDeclarativeEngine *m_engine;
    mongo::DBClientConnection *m_c;
};


#endif // QMONGODRIVER_H
