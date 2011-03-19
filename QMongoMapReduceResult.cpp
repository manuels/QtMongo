#include "QMongoDB.h"
#include "QMongoMapReduceResult.h"

QMongoMapReduceResult::QMongoMapReduceResult(QVariantMap resultObject, QObject *parent) :
    QMongoCollection(parent),
    m_resultObject(resultObject)
{
    qDebug() << "QMongoMapReduceResult::QMongoMapReduceResult";
    qDebug() << resultObject;
    m_resultName = resultObject["result"].toString();
}
