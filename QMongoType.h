#ifndef QMONGOTYPE_H
#define QMONGOTYPE_H

#include <QVariant>

#include <QObject>
#include <mongo/client/dbclient.h>

class QMongoType : public QObject
{
    Q_OBJECT
public:
    explicit QMongoType(QObject *parent = 0);
    explicit QMongoType(mongo::BSONObj b, QObject *parent = 0);

    mongo::BSONObj o;

signals:

public slots:

};
Q_DECLARE_METATYPE(QMongoType*)

#endif // QMONGOTYPE_H
