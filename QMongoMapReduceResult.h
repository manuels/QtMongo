#ifndef QMONGOMAPREDUCERESULT_H
#define QMONGOMAPREDUCERESULT_H

#include "QMongoCollection.h"

class QMongoMapReduceResult : public QMongoCollection
{
    Q_OBJECT

public:
    explicit QMongoMapReduceResult(QVariantMap resultObject = QVariantMap(), QObject *parent = 0);

signals:
    void error(QString errorMessage);

public slots:

protected:
    QString m_resultName;
    QVariantMap m_resultObject;
};

#endif // QMONGOMAPREDUCERESULT_H
