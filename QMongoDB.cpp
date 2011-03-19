#include <QDebug>
#include "QMongoCollection.h"
#include "QMongoDB.h"
#include "BSON.h"

QMongoDB::QMongoDB(QObject *parent) :
    QObject(parent),
    QDeclarativeParserStatus(),
    m_c(new mongo::DBClientConnection())
{
    qDebug() << "QMongoDB::QMongoDB()";
}

QMongoCollection* QMongoDB::collection(QString collection) {
    QMongoCollection* coll = new QMongoCollection(this);
    coll->setCollectionName(collection);
    return coll;
}

QMongoDB::~QMongoDB() {
    delete m_c;
}

void QMongoDB::componentComplete() {
    qDebug() << "QMongoDB componentComplete()";
    try{
        m_c->connect(host().toStdString());
    }
    catch( mongo::DBException &e ) {
        qDebug() << "QMongoDB connect() failed!!!";
    }
    qDebug() << "QMongoDB componentComplete() done";
}

QDeclarativeListProperty<QMongoCollection> QMongoDB::collections() {
/*)    QList<QMongoCollection*> colls;
    mongo::DBClientCursor* cursor = conn()->query("system.namespaces", mongo::Query()).release();

    int nsLength = dbName().length()+1;
    while(cursor->more()) {
        QString name = fromBson( cursor->next() )["name"].toString();

        if (name.indexOf("$") >= 0 && name.indexOf(".oplog.$") < 0) {
            continue;
        }

        colls.append(new QMongoCollection(name.mid(nsLength)));
    }

    delete(cursor); //!!!!!*/

    QDeclarativeListProperty<QMongoCollection> c(this, NULL, appendCollection, countCollections);
    return c;
}

void QMongoDB::appendCollection(QDeclarativeListProperty<QMongoCollection> *property, QMongoCollection *value) {
    qDebug() << "QMongoDB::appendCollection() currently is a NOOP";
/*    QMap<QString, QVariant> collections = _c.toMap();
    QMap<QString, QVariant> cmd;

    QMap<QString, QVariant>::Iterator i;
    for(i = collections.begin(); i != collections.end(); ++i) {
        cmd.clear();

        QString name = i.key();
        cmd = i.value().toMap();
        cmd["create"] = name;

        QString ns = dbName()+".$cmd";
        mongo::DBClientCursor* cursor = conn()->query(ns.toStdString(), toBson(cmd)).release();
        delete(cursor);
        // TODO: check cursor
    }
    */
}

bool QMongoDB::drop() {
    return conn()->dropDatabase(dbName().toStdString());
}

int QMongoDB::countCollections(QDeclarativeListProperty<QMongoCollection> *property) {
    qDebug() << "QMongoDB::countCollections() currently is a NOOP";
    qDebug() << property;
    return 0;
}

bool QMongoDB::collectionExists(QString ns) {
    return conn()->exists(ns.toStdString());
}
