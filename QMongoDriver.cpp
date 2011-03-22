#include <QDebug>
#include "BSON.h"
#include "QMongoDriver.h"

QMongoDriver::QMongoDriver(QObject *parent) :
    QObject(parent),
    m_c(new mongo::DBClientConnection())
{
}

QMongoDriver* QMongoDriver::init(QString host) {
    try{
        m_c->connect(host.toStdString());
    }
    catch( mongo::DBException &e ) {
        qCritical() << "QMongoDB connect() failed!!!";
    }
    return this;
}

QMongoCursor* QMongoDriver::find(QString ns, QVariantMap query, QVariantMap fields,
                        int limit, int skip, int batchSize, int options)
{
    mongo::DBClientCursor* cursor;
    cursor = conn()->query(ns.toStdString(),
                           mongo::Query(toBson(query)),
                           limit,
                           skip,
                           0, //toBson(fields), // TODO: fields are currently IGNORED!
                           options,
                           batchSize).release();

    return new QMongoCursor(cursor, this);
}

void QMongoDriver::insert(QString ns, QVariantMap object) {
    conn()->insert(ns.toStdString(), toBson(object));
}

void QMongoDriver::remove(QString ns, QVariantMap object, bool justOne) {
    conn()->remove(ns.toStdString(), mongo::Query(toBson(object)), justOne);
}

void QMongoDriver::update(QString ns, QVariantMap query, QVariantMap object, bool upsert, bool multi) {
    qDebug() << "QMongoDriver::update()" << ns << query << object;
    conn()->update(ns.toStdString(), mongo::Query(toBson(query)), toBson(object), upsert, multi);
}

void QMongoDriver::test(QVariant d) {
    qDebug() << d;
}

QVariantMap QMongoDriver::mapReduce(QString ns, QString map, QString reduce,
                             QVariantMap query, QString output)
{
    return fromBson(conn()->mapreduce(ns.toStdString(),
                                      map.toStdString(),
                                      reduce.toStdString(),
                                      toBson(query),
                                      output.toStdString()));
}

QString QMongoDriver::createObjectId() {
    mongo::OID oid;
    oid.init();
    return QString::fromStdString(oid.str());
}
