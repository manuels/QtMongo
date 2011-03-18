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
    query();
}

void QMongoQuery::query() {
    emit layoutAboutToBeChanged();
    int i=0;
    mongo::DBClientCursor* cursor = conn()->query(collection()->fullCollectionName().toStdString(), toBson(queryObject().toMap())).release();
    while(cursor->more()) {
        m_data << fromBson(cursor->next());
        ++i;
    }
    emit layoutChanged();
    qDebug() << "cursor contained" << i;

    delete cursor;
}

int QMongoQuery::rowCount(const QModelIndex &parent) const {
    return m_data.length();
}

QVariant QMongoQuery::data(const QModelIndex &index, int role) const {
    if (role != Qt::UserRole)
        return QVariant();
    else
        return m_data[index.row()];
}

QMongoQuery* QMongoQuery::forEach(QVariant v) {
    qDebug() << v;
    return this;
}

mongo::DBClientConnection* QMongoQuery::conn() {
    return collection()->db()->conn();
}
