#-------------------------------------------------
#
# Project created by QtCreator 2014-09-28T18:34:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapEditor
TEMPLATE = app
CONFIG += console
CONFIG += c++11

INCLUDEPATH += ../src
DEPENDPATH += ../src
INCLUDEPATH += ../include
DEPENDPATH += ../include

SOURCES += main.cpp\
        MapEditor.cpp \
    ../src/DataGateways/MapGateway.cpp \
    ../src/World/map.cpp \
    ../src/Actor/actor.cpp \
    ../src/DataGateways/TileDB.cpp \
    ../src/DataGateways/ActorDB.cpp

HEADERS  += MapEditor.h \
    ../src/Actor/ActorDescription.h \
    ../include/xml/rapidxml.hpp \
    ../include/xml/rapidxml_iterators.hpp \
    ../include/xml/rapidxml_print.hpp \
    ../include/xml/rapidxml_utils.hpp \
    ../src/DataGateways/MapGateway.h \
    ../src/World/map.h \
    ../src/World/MapId.h \
    ../src/Actor/actor.h \
    ../src/Actor/ActorType.h \
    ../src/DataGateways/TileDB.h \
    ../src/DataGateways/ActorDB.h

FORMS    += MapEditor.ui

win32: LIBS += -L$$PWD/../lib/ -ltcod-mingw

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
