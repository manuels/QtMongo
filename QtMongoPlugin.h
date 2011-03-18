#ifndef QTMONGOPLUGIN_H
#define QTMONGOPLUGIN_H

#include <QDeclarativeExtensionPlugin>

class QtMongoPlugin : public QDeclarativeExtensionPlugin
{
    Q_OBJECT
public:
    virtual void registerTypes(const char *uri);
};

#endif // QTMONGOPLUGIN_H
