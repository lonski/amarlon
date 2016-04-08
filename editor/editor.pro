#-------------------------------------------------
#
# Project created by QtCreator 2015-10-05T22:49:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = editor
TEMPLATE = app
CONFIG += c++11

SOURCES += main.cpp\
        editor.cpp \
    spells/spell_editor.cpp \
    spells/spell_edit.cpp \
    ../protobuf/src/spell.pb.cc \
    ../protobuf/src/skill.pb.cc \
    ../protobuf/src/tile.pb.cc \
    ../protobuf/src/drop_rule.pb.cc \
    ../protobuf/src/item_type.pb.cc \
    ../protobuf/src/utils.pb.cc \
    ../protobuf/src/actor.pb.cc \
    tiles/tiles_editor.cpp \
    tiles/tile_edit_dlg.cpp \
    actors/actors_editor.cpp \
    actors/actor_edit_dlg.cpp \
    actors/pickable_edit_dlg.cpp \
    actors/openable_edit_dlg.cpp \
    actors/ai_edit_dlg.cpp \
    actors/wearer_edit_dlg.cpp \
    actors/destroyable_edit_dlg.cpp \
    actors/drop_rule_edit_dlg.cpp \
    actors/inventory_edit_dlg.cpp \
    actors/character_edit_dlg.cpp \
    skills/skill_editor.cpp \
    skills/skill_edit.cpp \
    actors/actor_choose.cpp \
    actors/character_skill_edit.cpp \
    actors/spellbook_edit.cpp \
    actors/spell_select_dialog.cpp \
    actors/spell_slot_dialog.cpp \
    actors/item_slot_dialog.cpp

HEADERS  += editor.h \
    spells/spell_editor.h \
    ../protobuf/src/spell.pb.h \
    ../protobuf/src/skill.pb.h \
    ../protobuf/src/actor.pb.h \
    ../protobuf/src/tile.pb.h \
    ../protobuf/src/drop_rule.pb.h \
    ../protobuf/src/item_type.pb.h \
    ../protobuf/src/utils.pb.h \
    ../protobuf/src/actor.pb.h \
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
    actors/destroyable_edit_dlg.h \
    actors/drop_rule_edit_dlg.h \
    actors/inventory_edit_dlg.h \
    actors/character_edit_dlg.h \
    skills/skill_editor.h \
    skills/skill_edit.h \
    actors/actor_choose.h \
    actors/character_skill_edit.h \
    actors/spellbook_edit.h \
    actors/spell_select_dialog.h \
    actors/spell_slot_dialog.h \
    actors/item_slot_dialog.h

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
    actors/destroyable_edit_dlg.ui \
    actors/drop_rule_edit_dlg.ui \
    actors/inventory_edit_dlg.ui \
    actors/character_edit_dlg.ui \
    skills/skill_editor.ui \
    skills/skill_edit.ui \
    actors/actor_choose.ui \
    actors/character_skill_edit.ui \
    actors/spellbook_edit.ui \
    actors/spell_select_dialog.ui \
    actors/spell_slot_dialog.ui \
    actors/item_slot_dialog.ui

unix:!macx|win32: LIBS += -L$$PWD/../lib/ -lprotobuf

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../protobuf
INCLUDEPATH += actors
INCLUDEPATH += tiles
INCLUDEPATH += spells
INCLUDEPATH += skills
INCLUDEPATH += $$PWD/../protobuf/src
DEPENDPATH += $$PWD/../include
DEPENDPATH += $$PWD/../protobuf
DEPENDPATH += $$PWD/../protobuf/src
DEPENDPATH += spells
DEPENDPATH += skills
DEPENDPATH += actors
DEPENDPATH += tiles
