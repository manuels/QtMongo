#include <QDebug>
#include "BSON.h"

QVariantMap fromBson(mongo::BSONObj bson) {
    QVariantMap obj;

    for(mongo::BSONObjIterator i(bson); i.more();) {
        mongo::BSONElement e = i.next();
        QString name = e.fieldName();

        switch(e.type()) {
        case mongo::EOO:
            return obj;
        case mongo::NumberDouble:
            obj[name] = e.numberDouble();
            break;
        case mongo::String:
            obj[name] = QString::fromStdString(e.str());
            break;
        case mongo::Object:
            obj[name] = fromBson(e.embeddedObject());
            break;
        case mongo::Date:
            obj[name] = QDateTime::fromTime_t(e.date());
            break;
        case mongo::Undefined:
            obj[name] = QVariant();
            break;
        case mongo::jstOID:
            obj[name] = QString::fromStdString(e.__oid().str());
            break;
        case mongo::Bool:
            obj[name] = e.boolean();
            break;
        case mongo::CodeWScope:
            // TODO:
            qCritical() << "fromBson(): how should I handle CodeWScope types?";
            obj[name] = QVariant();
            break;
        case mongo::NumberInt:
            obj[name] = e.numberInt();
            break;
        default:
            qCritical() << "fromBson() type" << e.type() << "unknown!";
            Q_ASSERT(false);
        }
    }
    return obj;
}

mongo::BSONObj toBson(QVariantMap obj) {
    mongo::BSONObjBuilder b;

    QVariantMap::iterator it = obj.begin();
    while(it != obj.end()) {
        const char* name = it.key().toStdString().c_str();
        QVariant v = it.value();
        int type = v.type();

        bool ok = true;
        switch(type) {
        case QVariant::Int:
            b.append(name, v.toInt(&ok));
            break;
        case QVariant::String:
            b.append(name, v.toString().toStdString());
            break;
        case QVariant::LongLong:
            b.append(name, v.toLongLong(&ok));
            break;
        case QVariant::UInt:
            b.append(name, v.toUInt(&ok));
            break;
        case QVariant::Double:
            b.append(name, v.toDouble(&ok));
            break;
        case QVariant::Bool:
            b.appendBool(name, v.toBool());
            break;
        case QVariant::Time:
            b.appendTimeT(name, v.toDateTime().toTime_t());
            break;
        case QVariant::Invalid:
            b.appendUndefined(name);
            break;
        default:
            qCritical() << "toBsonObj() failed to convert" << obj << "for" << name << "with type" << type;
            ok = false;
        }
        Q_ASSERT(ok);
        ++it;
    }
    return b.obj();
}
