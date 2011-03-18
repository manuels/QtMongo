#ifndef QMONGOCOLLECTION_H
#define QMONGOCOLLECTION_H

#include <QObject>
#include <QVariant>
#include <QStringList>
#include <QMap>

#include <mongo/client/dbclient.h>

class QMongoDB;
class QMongoQuery;

class QMongoCollection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ collectionName WRITE setCollectionName)

public:
    explicit QMongoCollection(QObject *parent = 0);
    explicit QMongoCollection(QString name, QObject *parent = 0);

    Q_INVOKABLE
    QMongoQuery* find(QMap<QString, QVariant> query);

    Q_INVOKABLE
    void insert(QMap<QString, QVariant> data);

    Q_INVOKABLE
    void update(QMap<QString, QVariant> query,
                QMap<QString, QVariant> obj,
                QMap<QString, QVariant> flags = QMap<QString, QVariant>());

    QString fullCollectionName();
    QString collectionName() { return collName;}
    void setCollectionName(QString newName) { collName = newName; }

    Q_INVOKABLE
    QVariant mapReduce(QString map, QString reduce);

    QMongoDB* db();
    mongo::DBClientConnection* conn();
signals:

public slots:

protected:
    QString collName;
};

Q_DECLARE_METATYPE(QMongoCollection*)

#endif // QMONGOCOLLECTION_H
