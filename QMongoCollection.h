#ifndef QMONGOCOLLECTION_H
#define QMONGOCOLLECTION_H

#include <QObject>
#include <QVariant>
#include <QStringList>
#include <QMap>

#include <mongo/client/dbclient.h>

class QMongoDB;
class QMongoQuery;
class QMongoMapReduceResult;

class QMongoCollection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ collectionName WRITE setCollectionName)

public:
    explicit QMongoCollection(QObject *parent = 0);
    explicit QMongoCollection(QString name, QObject *parent = 0);

    Q_INVOKABLE
    QMongoQuery* find(QVariantMap query = QVariantMap());

    Q_INVOKABLE
    QVariantMap findOne(QVariantMap query = QVariantMap());

    Q_INVOKABLE
    void insert(QVariantMap data);

    Q_INVOKABLE
    void remove(QVariantMap  query,
                QVariantMap flags);

    Q_INVOKABLE
    void update(QVariantMap query,
                QVariantMap obj,
                QVariantMap flags = QVariantMap());

    virtual QString fullCollectionName();
    virtual QString collectionName() { return collName;}
    void setCollectionName(QString newName) { collName = newName; }

    Q_INVOKABLE
    bool drop();

    Q_INVOKABLE
    QMongoMapReduceResult* mapReduce(QString map, QString reduce,
                                     QVariantMap query = QVariantMap(),
                                     QString output = "");

    QMongoDB* db();
    mongo::DBClientConnection* conn();
signals:

public slots:

protected:
    QString collName;
};

Q_DECLARE_METATYPE(QMongoCollection*)

#endif // QMONGOCOLLECTION_H
