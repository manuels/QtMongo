#include <QDebug>

#include "BSON.h"
#include "QMongoCursor.h"

QMongoCursor::QMongoCursor(mongo::DBClientCursor* cursor, QObject *parent) :
    QObject(parent),
    m_cursor(cursor)
{
    Q_ASSERT(cursor);
}

QMongoCursor::~QMongoCursor() {
    delete m_cursor;
}

QVariantMap QMongoCursor::next() {
    return fromBson(cursor()->next());
}

bool QMongoCursor::hasNext() {
    return cursor()->more();
}
