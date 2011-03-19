#ifndef QMONGODB_H
#define QMONGODB_H
#include <QDebug>

#include <QObject>
#include <QDeclarativeParserStatus>
#include <QDeclarativeListProperty>

#include <mongo/client/dbclient.h>

class QMongoCollection;


class QMongoDB : public QObject, public QDeclarativeParserStatus
{
    Q_OBJECT
    Q_INTERFACES(QDeclarativeParserStatus)
    Q_PROPERTY(QString name READ dbName WRITE setDbName)
    Q_PROPERTY(QString host READ host WRITE setHost)
    Q_PROPERTY(QDeclarativeListProperty<QMongoCollection> collections READ collections);

public:
    explicit QMongoDB(QObject *parent = NULL);

    Q_INVOKABLE
    QMongoCollection* collection(QString collection);

    Q_INVOKABLE
    bool drop();

    void classBegin() {}
    void componentComplete();

    QString dbName() { return m_name; }
    void setDbName(QString newName) { m_name = newName; }

    QString host() { return m_host; }
    void setHost(QString newHost) { m_host = newHost; }

    QDeclarativeListProperty<QMongoCollection> collections();
    static void appendCollection(QDeclarativeListProperty<QMongoCollection> *property, QMongoCollection *value);
    static int countCollections(QDeclarativeListProperty<QMongoCollection> *property);
    Q_INVOKABLE
    bool collectionExists(QString ns);

    mongo::DBClientConnection* conn() { Q_ASSERT(m_c); return m_c; }

    ~QMongoDB();
signals:

public slots:

protected:
    QString m_name;
    QString m_host;
    mongo::DBClientConnection *m_c;
};

#endif // QMONGODB_H
