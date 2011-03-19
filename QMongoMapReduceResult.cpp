#include "QMongoDB.h"
#include "QMongoMapReduceResult.h"

QMongoMapReduceResult::QMongoMapReduceResult(QVariantMap resultObject, QObject *parent) :
    QMongoCollection(parent),
    m_resultObject(resultObject)
{
    qDebug() << "QMongoMapReduceResult::QMongoMapReduceResult()" << resultObject;
    setCollectionName(resultObject["result"].toString());

    qDebug() << "Collection Exists?" << db()->collectionExists(fullCollectionName());

    if (resultObject.contains("errmsg") )
        emit error(resultObject["errmsg"].toString());
}
