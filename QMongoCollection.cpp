#include <QDebug>

#include "QMongoDB.h"
#include "QMongoQuery.h"
#include "QMongoCollection.h"
#include "QMongoMapReduceResult.h"
#include "BSON.h"

QMongoCollection::QMongoCollection(QObject *parent) :
    QObject(parent)
{
}

QMongoCollection::QMongoCollection(QString name, QObject *parent) :
    QObject(parent)
{
    setCollectionName(name);
}


QMongoQuery* QMongoCollection::find(QVariantMap query) {
    QMongoQuery *q = new QMongoQuery(this);
    q->setCollection(this);
    q->setQueryObject(query);
    q->query();
    return q;
}

QMongoDB* QMongoCollection::db() {
    QMongoDB *db = qobject_cast<QMongoDB*>(parent());
    Q_ASSERT(db);
    return db;
}

mongo::DBClientConnection* QMongoCollection::conn() {
    return db()->conn();
}

void QMongoCollection::insert(QMap<QString, QVariant> data) {
    conn()->insert(fullCollectionName().toStdString(), toBson(data));
}

void QMongoCollection::update(QMap<QString, QVariant> query,
                              QMap<QString, QVariant> obj,
                              QMap<QString, QVariant> flags)
{
    bool upsert = flags["upsert"].toBool();
    bool multi = flags["muli"].toBool();

    conn()->update(fullCollectionName().toStdString(),
                   toBson(query),
                   toBson(obj), upsert, multi);
}

QString QMongoCollection::fullCollectionName() {
    return db()->dbName()+"."+collName;
}

QMongoMapReduceResult* QMongoCollection::mapReduce(QString map, QString reduce) {
    qDebug() << "QMongoCollection::mapReduce(): " << fullCollectionName() << map << reduce;
    mongo::BSONObj b = conn()->mapreduce(fullCollectionName().toStdString(), map.toStdString(), reduce.toStdString());

    QVariantMap resultObject = fromBson(b);
    return new QMongoMapReduceResult(resultObject, db());
}
