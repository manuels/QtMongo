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
    qDebug() << "QMongoDriver::find()" << ns << query;
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
