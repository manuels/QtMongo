TEMPLATE = lib
CONFIG += qt plugin
QT += declarative

TARGET = qtmongodb

DESTDIR = lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

HEADERS += \
    QtMongoPlugin.h \
    BSON.h \
    QMongoDriver.h \
    QMongoCursor.h

SOURCES += \
    QtMongoPlugin.cpp \
    BSON.cpp \
    QMongoDriver.cpp \
    QMongoCursor.cpp

OTHER_FILES += \
    demo.qml \
    qmldir \
    README \
    LICENSE \
    json/JsonEdit.qml \
    json/json2.js \
    Button.qml \
    QtMongo/MongoDB.qml \
    QtMongo/mongoenv.js

LIBS += -lmongoclient \
    -lboost_thread-mt -lboost_filesystem -lboost_program_options

unix:!macx:!symbian: PRE_TARGETDEPS += /usr/lib/libmongoclient.a
