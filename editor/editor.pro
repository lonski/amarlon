#-------------------------------------------------
#
# Project created by QtCreator 2015-10-05T22:49:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = editor
TEMPLATE = app
CONFIG += c++14

SOURCES += main.cpp\
        editor.cpp \
    spell_editor.cpp \
    ../src/spells/protobuf/spells.pb.cc \
    spell_edit.cpp

HEADERS  += editor.h \
    spell_editor.h \
    ../src/spells/protobuf/spells.pb.h \
    spell_edit.h \
    enum_mappings.h

FORMS    += editor.ui \
    spell_editor.ui \
    spell_edit.ui

unix:!macx|win32: LIBS += -L$$PWD/../lib/ -lprotobuf

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += ../src/spells/protobuf
DEPENDPATH += $$PWD/../include
