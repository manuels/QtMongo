#ifndef QMONGOCURSOR_H
#define QMONGOCURSOR_H
#include <QDebug>

#include <QAbstractListModel>
#include <QDeclarativeParserStatus>
#include <mongo/client/dbclient.h>

class QMongoDB;
class QMongoCollection;

class QMongoQuery : public QAbstractListModel, public QVariantList, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QVariantMap query READ queryObject WRITE setQueryObject)
    Q_PROPERTY(QMongoCollection* collection READ collection WRITE setCollection)
public:
    QMongoQuery(QObject *parent = NULL);

    Q_INVOKABLE
    QVariant get(int i) const { return at(i); }

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

    QVariantMap queryObject() { return m_queryObject; }
    void setQueryObject(QVariantMap query) { qDebug() << "QMongoQuery::setQueryObject()" << query;
                                                      m_queryObject = query; }

    void classBegin() {};
    void componentComplete();

    QMongoCollection* collection() { return m_collection; }
    void setCollection(QMongoCollection* collection) { m_collection = collection; }

    mongo::DBClientConnection* conn();

    void query();
signals:

public slots:

protected:
    QString m_nameSpace;
    QVariantMap m_queryObject;
    QMongoCollection *m_collection;
};

#endif // QMONGOCURSOR_H
