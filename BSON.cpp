#include <QDebug>
#include "BSON.h"

QVariantMap fromBson(mongo::BSONObj bson) {
    QVariantMap obj;

    for(mongo::BSONObjIterator i(bson); i.more();) {
        mongo::BSONElement e = i.next();
        QString name = QString::fromStdString(e.fieldName());

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
        case mongo::jstNULL:
            obj[name] = QVariant();
            break;
        case mongo::Bool:
            obj[name] = e.boolean();
            break;
        case mongo::CodeWScope:
            obj[name] = "MongoCode["+QString::fromStdString(e.codeWScopeCode())+"]";
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
        QByteArray byteName = it.key().toStdString().c_str();
        const char* name = byteName.constData();
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
        case QVariant::Map:
            if (v.toMap().value("__TYPE__").toString() == "THIS_IS_MONGO_CODE") {
                QString code = v.toMap().value("__code").toString();
                QVariantMap scope = v.toMap().value("__scope").toMap();
                b.appendCodeWScope(name, code.toStdString().c_str(), toBson(scope));
            }
            else
                b.append(name, toBson(v.toMap()));
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
            qCritical() << "toBsonObj() failed to convert" << obj << "for" << name << "with type" << v.typeName();
            ok = false;
        }
        Q_ASSERT(ok);
        ++it;
    }
    return b.obj();
}
