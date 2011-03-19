TEMPLATE = lib
CONFIG += qt plugin
QT += declarative

TARGET = qtmongodb

DESTDIR = lib
OBJECTS_DIR = tmp
MOC_DIR = tmp

HEADERS += \
    QtMongoPlugin.h \
    QMongoDB.h \
    QMongoCollection.h \
    BSON.h \
    QMongoQuery.h \
    QMongoMapReduceResult.h

SOURCES += \
    QtMongoPlugin.cpp \
    QMongoDB.cpp \
    QMongoCollection.cpp \
    BSON.cpp \
    QMongoQuery.cpp \
    QMongoMapReduceResult.cpp

OTHER_FILES += \
    demo.qml \
    qmldir \
    README

LIBS += -lmongoclient \
    -lboost_thread-mt -lboost_filesystem -lboost_program_options

unix:!macx:!symbian: PRE_TARGETDEPS += /usr/lib/libmongoclient.a
