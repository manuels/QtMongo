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
    mongo::Query q(toBson(query));
    mongo::DBClientCursor* cursor;
    qDebug() << "MongoDriver::find" << ns << QString::fromStdString(q.toString());
    cursor = conn()->query(ns.toStdString(),
                           q,
                           limit,
                           skip,
                           0, //toBson(fields), // TODO: fields are currently IGNORED!
                           options,
                           batchSize).release();

    return new QMongoCursor(cursor, this);
}

void QMongoDriver::insert(QString ns, QVariantMap object) {
    mongo::BSONObj obj(toBson(object));
    qDebug() << "QMongoDriver::insert" << ns << QString::fromStdString(obj);
    conn()->insert(ns.toStdString(), obj);
}

void QMongoDriver::remove(QString ns, QVariantMap object, bool justOne) {
    conn()->remove(ns.toStdString(), mongo::Query(toBson(object)), justOne);
}

void QMongoDriver::update(QString ns, QVariantMap query, QVariantMap object, bool upsert, bool multi) {
    mongo::Query q(toBson(query));
    qDebug() << "QMongoDriver::update()" << ns << QString::fromStdString(q) << object;
    conn()->update(ns.toStdString(), q, toBson(object), upsert, multi);
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

QMongoType* QMongoDriver::createObjectId(QVariantMap objId) {
    mongo::BSONObjBuilder b;

    qDebug() << "QMongoDriver::createObjectId():" << objId;
    mongo::OID oid;
    QString idStr = objId["str"].toString();
    if (!idStr.isNull())
        oid.init( idStr.toStdString() );
    else
        oid.init();
    b.append("value", oid);

    mongo::BSONObj o = b.obj();
    qDebug() << "QMongoDriver::createObjectId" << QString::fromStdString(o.jsonString());
    return new QMongoType(o, this);
}

QMongoType* QMongoDriver::createFunction(QString code, QVariantMap scope) {
    mongo::BSONObjBuilder b;
    b.appendCodeWScope("value", code.toStdString().c_str(), toBson(scope));
    return new QMongoType(b.obj(), this);
}
