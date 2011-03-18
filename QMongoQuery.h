#ifndef QMONGOCURSOR_H
#define QMONGOCURSOR_H

#include <QAbstractListModel>
#include <QDeclarativeParserStatus>
#include <mongo/client/dbclient.h>

class QMongoDB;
class QMongoCollection;

class QMongoQuery : public QAbstractListModel, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QVariant query READ queryObject WRITE setQueryObject)
    Q_PROPERTY(QMongoCollection* collection READ collection WRITE setCollection)
public:
    QMongoQuery(QObject *parent = NULL);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QVariant queryObject() { return m_queryObject; }
    void setQueryObject(QVariant query) { m_queryObject = query; }

    Q_INVOKABLE
    QMongoQuery* forEach(QVariant v);

    void classBegin() {};
    void componentComplete();

    QMongoCollection* collection() { return m_collection; }
    void setCollection(QMongoCollection* collection) { m_collection = collection; }

    mongo::DBClientConnection* conn();

    void query();
signals:

public slots:

protected:
    QVariant m_queryObject;
    QMongoCollection *m_collection;
    QList<QVariant> m_data;
};

#endif // QMONGOCURSOR_H
