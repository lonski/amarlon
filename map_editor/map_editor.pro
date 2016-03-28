#-------------------------------------------------
#
# Project created by QtCreator 2014-09-28T18:34:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = map_editor
TEMPLATE = app
CONFIG += console
CONFIG += c++11

unix: LIBS += -L$$PWD/../lib/ -ltcod
unix: LIBS += -L$$PWD/../lib/ -ltcodxx

INCLUDEPATH += ../src
INCLUDEPATH += ../src/utils
INCLUDEPATH += ../src/world
DEPENDPATH += ../src
INCLUDEPATH += ../include
DEPENDPATH += ../include
INCLUDEPATH += ../include/tcod
DEPENDPATH += ../include/tcod

SOURCES += main.cpp\
        map_editor.cpp \
    map/map_data.cpp

HEADERS  += map_editor.h \
    map/map_data.h \
    map/serialized_tile.h

FORMS    += map_editor.ui
