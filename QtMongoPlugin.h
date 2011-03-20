#ifndef QTMONGOPLUGIN_H
#define QTMONGOPLUGIN_H

#include <QDeclarativeExtensionPlugin>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>

class QtMongoPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void initializeEngine(QDeclarativeEngine *engine, const char *uri);
    virtual void registerTypes(const char *uri);
};

#endif // QTMONGOPLUGIN_H
