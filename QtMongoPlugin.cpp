#include "QtMongoPlugin.h"
#include "QMongoDB.h"
#include "QMongoCollection.h"
#include "QMongoQuery.h"
#include "QMongoMapReduceResult.h"
#include <qdeclarative.h>

void QtMongoPlugin::registerTypes(const char *uri)
{
    qmlRegisterType<QMongoDB>(uri, 1, 0, "MongoDB");
    qmlRegisterType<QMongoCollection>(uri, 1, 0, "MongoCollection");
    qmlRegisterType<QMongoQuery>(uri, 1, 0, "MongoQuery");
    qmlRegisterUncreatableType<QMongoMapReduceResult>(uri, 1, 0, "MongoMapReduceResult",
        QString("you cannot create map reduce results. use collection.mapReduce()"));
}

Q_EXPORT_PLUGIN2(qtmongodb, QtMongoPlugin);

