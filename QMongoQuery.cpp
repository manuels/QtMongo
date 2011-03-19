#include <QDebug>
#include "QMongoDB.h"
#include "QMongoCollection.h"
#include "QMongoQuery.h"
#include "BSON.h"

QMongoQuery::QMongoQuery(QObject *parent) :
    QAbstractListModel(parent),
    QDeclarativeParserStatus()
{
    QHash<int, QByteArray> roleNames;
    roleNames[Qt::UserRole] = "obj";
    setRoleNames(roleNames);
}

void QMongoQuery::componentComplete() {
    qDebug() << "QMongoQuery::componentComplete() queryObject:" << queryObject();
    query();
}

void QMongoQuery::query() {
    qDebug() << "QMongoQuery::query()" <<
        collection()->fullCollectionName() << queryObject();

    emit layoutAboutToBeChanged();
    clear();

    int i=0;
    QString ns = collection()->fullCollectionName();
    mongo::DBClientCursor* cursor =
            conn()->query(ns.toStdString(), toBson(queryObject())).release();
    while(cursor->more()) {
        append( fromBson(cursor->next()) );
        ++i;
    }
    qDebug() << "cursor contained" << i;

    delete cursor;
    emit layoutChanged();
}

int QMongoQuery::rowCount(const QModelIndex &parent) const {
    return length();
}

QVariant QMongoQuery::data(const QModelIndex &index, int role) const {
    if (role != Qt::UserRole)
        return QVariant();
    else
        return get(index.row());
}

mongo::DBClientConnection* QMongoQuery::conn() {
    return collection()->db()->conn();
}
