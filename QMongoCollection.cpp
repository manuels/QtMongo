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
    qDebug() << "QMongoCollection::find()" << fullCollectionName() << query;
    QMongoQuery *q = new QMongoQuery(this);
    q->setCollection(this);
    q->setQueryObject(query);
    q->query();
    return q;
}

Q_INVOKABLE
QVariantMap QMongoCollection::findOne(QVariantMap query) {
    return fromBson(
                conn()->findOne(fullCollectionName().toStdString(),
                                toBson(query)));
}


QMongoDB* QMongoCollection::db() {
    QMongoDB *db = qobject_cast<QMongoDB*>(parent());
    Q_ASSERT(db);
    return db;
}

mongo::DBClientConnection* QMongoCollection::conn() {
    return db()->conn();
}

void QMongoCollection::insert(QVariantMap data) {
    conn()->insert(fullCollectionName().toStdString(), toBson(data));
}

void QMongoCollection::update(QVariantMap query,
                              QVariantMap obj,
                              QVariantMap flags)
{
    bool upsert = flags["upsert"].toBool();
    bool multi = flags["muli"].toBool();

    conn()->update(fullCollectionName().toStdString(),
                   toBson(query),
                   toBson(obj), upsert, multi);
}

void QMongoCollection::remove(QVariantMap query,
                              QVariantMap flags)
{
    bool justOne = flags["justOne"].toBool();

    conn()->remove(fullCollectionName().toStdString(),
                   toBson(query),
                   justOne);
}

QString QMongoCollection::fullCollectionName() {
    return db()->dbName()+"."+collName;
}

QMongoMapReduceResult* QMongoCollection::mapReduce(QString map, QString reduce,
                                                   QVariantMap query, QString output) {
    mongo::BSONObj b = conn()->mapreduce(fullCollectionName().toStdString(),
                                         map.toStdString(),
                                         reduce.toStdString(),
                                         toBson(query),
                                         output.toStdString());

    QVariantMap resultObject = fromBson(b);
    return new QMongoMapReduceResult(resultObject, db());
}

bool QMongoCollection::drop() {
    return conn()->dropCollection(fullCollectionName().toStdString());
}
