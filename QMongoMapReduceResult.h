#ifndef QMONGOMAPREDUCERESULT_H
#define QMONGOMAPREDUCERESULT_H

#include "QMongoCollection.h"

class QMongoMapReduceResult : public QMongoCollection
{
    Q_OBJECT
    Q_PROPERTY(int timeMillis READ timeMillis)
    Q_PROPERTY(bool ok READ ok)

public:
    explicit QMongoMapReduceResult(QVariantMap resultObject = QVariantMap(), QObject *parent = 0);

    int timeMillis() { return m_resultObject["timeMillis"].toInt(); }
    bool ok() { return m_resultObject["ok"].toBool(); }

    virtual QString fullCollectionName() { return m_resultName; }

signals:

public slots:

protected:
    QString m_resultName;
    QVariantMap m_resultObject;
};

#endif // QMONGOMAPREDUCERESULT_H
