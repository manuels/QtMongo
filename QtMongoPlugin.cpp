#include <QDebug>
#include "QtMongoPlugin.h"
#include "QMongoDriver.h"
#include <qdeclarative.h>

void QtMongoPlugin::registerTypes(const char *uri)
{
    qmlRegisterUncreatableType<QMongoDriver>(uri, 1, 0, "MongoDriver",
        QString("you cannot create a new MongoDriver!"));
    qmlRegisterUncreatableType<QMongoCursor>(uri, 1, 0, "MongoCursor",
        QString("you cannot create a new MongoCursor!"));
    qmlRegisterUncreatableType<QMongoType>(uri, 1, 0, "MongoType",
        QString("you cannot create a new MongoType!"));
}

void QtMongoPlugin::initializeEngine(QDeclarativeEngine *engine, const char *uri) {
    QDeclarativeContext *ctx = engine->rootContext();
    ctx->setContextProperty("mongoDriver", new QMongoDriver(this));
}

Q_EXPORT_PLUGIN2(qtmongodb, QtMongoPlugin);

