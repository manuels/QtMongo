#include <QDebug>
#include "QMongoType.h"

QMongoType::QMongoType(mongo::BSONObj b, QObject *parent) :
    QObject(parent),
    o(b)
{
}

QMongoType::QMongoType(QObject *parent) :
    QObject(parent)
{
}
