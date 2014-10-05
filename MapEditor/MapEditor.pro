#-------------------------------------------------
#
# Project created by QtCreator 2014-09-28T18:34:08
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MapEditor
TEMPLATE = app
CONFIG -= console
CONFIG += c++11

INCLUDEPATH += ../src
DEPENDPATH += ../src

SOURCES += main.cpp\
        MapEditor.cpp \
    ../src/World/MapDescription.cpp \
    ../src/Persistence/DataGateway.cpp

HEADERS  += MapEditor.h \
    ../src/World/mapdescription.h \
    ../src/Actor/ActorDescription.h \
    ../src/Persistence/DataGateway.h

FORMS    += MapEditor.ui
