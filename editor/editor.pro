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
    spells/spell_editor.cpp \
    ../src/spells/protobuf/spells.pb.cc \
    ../src/world/protobuf/tiles.pb.cc \
    spells/spell_edit.cpp \
    tiles/tiles_editor.cpp \
    tiles/tile_edit_dlg.cpp

HEADERS  += editor.h \
    spells/spell_editor.h \
    ../src/spells/protobuf/spells.pb.h \
    ../src/world/protobuf/tiles.pb.h \
    spells/spell_edit.h \
    enum_mappings.h \
    tiles/tiles_editor.h \
    tiles/tile_edit_dlg.h

FORMS    += editor.ui \
    spells/spell_editor.ui \
    spells/spell_edit.ui \
    tiles/tiles_editor.ui \
    tiles/tileeditdlg.ui

unix:!macx|win32: LIBS += -L$$PWD/../lib/ -lprotobuf

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += ../src/spells/protobuf
INCLUDEPATH += ../src/world/protobuf
INCLUDEPATH += spells
INCLUDEPATH += tiles
DEPENDPATH += $$PWD/../include
