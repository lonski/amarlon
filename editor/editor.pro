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
    ../src/protobuf/spells/spells.pb.cc \
    ../src/protobuf/tiles/tiles.pb.cc \
    ../src/protobuf/actors/actors.pb.cc \
    spells/spell_edit.cpp \
    tiles/tiles_editor.cpp \
    tiles/tile_edit_dlg.cpp \
    actors/actors_editor.cpp \
    actors/actor_edit_dlg.cpp \
    actors/pickable_edit_dlg.cpp \
    actors/openable_edit_dlg.cpp \
    actors/ai_edit_dlg.cpp \
    actors/wearer_edit_dlg.cpp \
    actors/item_slot_edit_dlg.cpp \
    actors/destroyable_edit_dlg.cpp \
    actors/drop_rule_edit_dlg.cpp \
    actors/inventory_edit_dlg.cpp \
    actors/character_edit_dlg.cpp

HEADERS  += editor.h \
    spells/spell_editor.h \
    ../src/protobuf/spells/spells.pb.h \
    ../src/protobuf/tiles/tiles.pb.h \
    ../src/protobuf/actors/actors.pb.h \
    spells/spell_edit.h \
    enum_mappings.h \
    tiles/tiles_editor.h \
    tiles/tile_edit_dlg.h \
    actors/actors_editor.h \
    actors/actor_edit_dlg.h \
    actors/pickable_edit_dlg.h \
    actors/openable_edit_dlg.h \
    actors/ai_edit_dlg.h \
    actors/wearer_edit_dlg.h \
    actors/item_slot_edit_dlg.h \
    actors/destroyable_edit_dlg.h \
    actors/drop_rule_edit_dlg.h \
    actors/inventory_edit_dlg.h \
    actors/character_edit_dlg.h

FORMS    += editor.ui \
    spells/spell_editor.ui \
    spells/spell_edit.ui \
    tiles/tiles_editor.ui \
    tiles/tileeditdlg.ui \
    actors/actors_editor.ui \
    actors/actor_edit_dlg.ui \
    actors/pickable_edit_dlg.ui \
    actors/openable_edit_dlg.ui \
    actors/ai_edit_dlg.ui \
    actors/wearer_edit_dlg.ui \
    actors/item_slot_edit_dlg.ui \
    actors/destroyable_edit_dlg.ui \
    actors/drop_rule_edit_dlg.ui \
    actors/inventory_edit_dlg.ui \
    actors/character_edit_dlg.ui

unix:!macx|win32: LIBS += -L$$PWD/../lib/ -lprotobuf

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += ../src/protobuf
INCLUDEPATH += spells
INCLUDEPATH += tiles
DEPENDPATH += $$PWD/../include
