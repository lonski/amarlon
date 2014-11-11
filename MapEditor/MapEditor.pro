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

unix: LIBS += -L$$PWD/../lib/ -ltcod
unix: LIBS += -L$$PWD/../lib/ -ltcodxx

INCLUDEPATH += ../src
DEPENDPATH += ../src
INCLUDEPATH += ../include
DEPENDPATH += ../include
INCLUDEPATH += ../include/libtcod
DEPENDPATH += ../include/libtcod

SOURCES += main.cpp\
        MapEditor.cpp \
    ../src/Actor/ActorFeatures/Ai/Ai.cpp \
    ../src/Actor/ActorFeatures/Ai/MonsterAi.cpp \
    ../src/Actor/ActorFeatures/Openable/Openable.cpp \
    ../src/Actor/ActorFeatures/Openable/OpenableContainer.cpp \
    ../src/Actor/ActorFeatures/Openable/OpenableDoor.cpp \
    ../src/Actor/ActorFeatures/Wearer/wearer.cpp \
    ../src/Actor/ActorFeatures/ActorFeature.cpp \
    ../src/Actor/ActorFeatures/Container.cpp \
    ../src/Actor/ActorFeatures/Fighter.cpp \
    ../src/Actor/ActorFeatures/Pickable.cpp \
    ../src/Actor/Effects/Effect.cpp \
    ../src/Actor/Effects/LockEffect.cpp \
    ../src/Actor/Effects/SelfHealEffect.cpp \
    ../src/Actor/Actor.cpp \
    ../src/Commands/cmd_put_into.cpp \
    ../src/Commands/CmdClose.cpp \
    ../src/Commands/CmdFullscreen.cpp \
    ../src/Commands/CmdHelp.cpp \
    ../src/Commands/CmdInventory.cpp \
    ../src/Commands/CmdMove.cpp \
    ../src/Commands/CmdOpen.cpp \
    ../src/Commands/CmdPick.cpp \
    ../src/Commands/CmdUse.cpp \
    ../src/Commands/Command.cpp \
    ../src/DataGateways/Parsers/ActorParser.cpp \
    ../src/DataGateways/ActorDB.cpp \
    ../src/DataGateways/MapGateway.cpp \
    ../src/DataGateways/TileDB.cpp \
    ../src/gui/widget/menu/items_menu.cpp \
    ../src/gui/widget/menu/label_menu_item.cpp \
    ../src/gui/widget/menu/menu.cpp \
    ../src/gui/widget/menu/slot_menu_item.cpp \
    ../src/gui/widget/bar.cpp \
    ../src/gui/widget/label.cpp \
    ../src/gui/widget/list.cpp \
    ../src/gui/widget/panel.cpp \
    ../src/gui/widget/widget.cpp \
    ../src/gui/window/inventory_window/bag_manager.cpp \
    ../src/gui/window/inventory_window/body_manager.cpp \
    ../src/gui/window/inventory_window/inventory_window.cpp \
    ../src/gui/window/text_window/resizeable_text_window.cpp \
    ../src/gui/window/text_window/text_window.cpp \
    ../src/gui/window/amount_window.cpp \
    ../src/gui/window/pick_up_window.cpp \
    ../src/gui/window/window.cpp \
    ../src/gui/window/window_manager.cpp \
    ../src/gui/gui.cpp \
    ../src/utils/target_selector/executor_selector.cpp \
    ../src/utils/target_selector/single_neighbour_selector.cpp \
    ../src/utils/target_selector/target_selector.cpp \
    ../src/utils/configuration.cpp \
    ../src/utils/direction_selector.cpp \
    ../src/utils/item_picker.cpp \
    ../src/utils/messenger.cpp \
    ../src/utils/utils.cpp \
    ../src/world/map.cpp \
    ../src/command_executor.cpp \
    ../src/engine.cpp

HEADERS  += MapEditor.h \
    ../src/Actor/ActorFeatures/Ai/Ai.h \
    ../src/Actor/ActorFeatures/Ai/AiType.h \
    ../src/Actor/ActorFeatures/Ai/MonsterAi.h \
    ../src/Actor/ActorFeatures/Openable/Openable.h \
    ../src/Actor/ActorFeatures/Openable/OpenableContainer.h \
    ../src/Actor/ActorFeatures/Openable/OpenableDoor.h \
    ../src/Actor/ActorFeatures/Openable/OpenableType.h \
    ../src/Actor/ActorFeatures/Wearer/item_slot_type.h \
    ../src/Actor/ActorFeatures/Wearer/wearer.h \
    ../src/Actor/ActorFeatures/ActorFeature.h \
    ../src/Actor/ActorFeatures/Container.h \
    ../src/Actor/ActorFeatures/Fighter.h \
    ../src/Actor/ActorFeatures/Pickable.h \
    ../src/Actor/ActorFeatures/pickable_category.h \
    ../src/Actor/Effects/Effect.h \
    ../src/Actor/Effects/EffectType.h \
    ../src/Actor/Effects/LockEffect.h \
    ../src/Actor/Effects/SelfHealEffect.h \
    ../src/Actor/Actor.h \
    ../src/Actor/ActorType.h \
    ../src/Commands/cmd_put_into.h \
    ../src/Commands/CmdClose.h \
    ../src/Commands/CmdFullscreen.h \
    ../src/Commands/CmdHelp.h \
    ../src/Commands/CmdInventory.h \
    ../src/Commands/CmdMove.h \
    ../src/Commands/CmdOpen.h \
    ../src/Commands/CmdPick.h \
    ../src/Commands/CmdUse.h \
    ../src/Commands/Command.h \
    ../src/DataGateways/Parsers/ActorParser.h \
    ../src/DataGateways/ActorDB.h \
    ../src/DataGateways/ActorDescriptions.h \
    ../src/DataGateways/MapGateway.h \
    ../src/DataGateways/TileDB.h \
    ../src/gui/widget/menu/items_menu.h \
    ../src/gui/widget/menu/label_menu_item.h \
    ../src/gui/widget/menu/menu.h \
    ../src/gui/widget/menu/menu_item.h \
    ../src/gui/widget/menu/slot_menu_item.h \
    ../src/gui/widget/bar.h \
    ../src/gui/widget/label.h \
    ../src/gui/widget/list.h \
    ../src/gui/widget/panel.h \
    ../src/gui/widget/widget.h \
    ../src/gui/window/inventory_window/bag_manager.h \
    ../src/gui/window/inventory_window/body_manager.h \
    ../src/gui/window/inventory_window/inventory_window.h \
    ../src/gui/window/text_window/resizeable_text_window.h \
    ../src/gui/window/text_window/text_window.h \
    ../src/gui/window/amount_window.h \
    ../src/gui/window/pick_up_window.h \
    ../src/gui/window/window.h \
    ../src/gui/window/window_manager.h \
    ../src/gui/gui.h \
    ../src/gui/message_box.h \
    ../src/utils/target_selector/executor_selector.h \
    ../src/utils/target_selector/single_neighbour_selector.h \
    ../src/utils/target_selector/target_selector.h \
    ../src/utils/amarlon_except.h \
    ../src/utils/colored_string.h \
    ../src/utils/configuration.h \
    ../src/utils/direction_selector.h \
    ../src/utils/item_picker.h \
    ../src/utils/messenger.h \
    ../src/utils/selector_type.h \
    ../src/utils/singleton.h \
    ../src/utils/utils.h \
    ../src/utils/xml_utils.h \
    ../src/world/map.h \
    ../src/world/map_id.h \
    ../src/world/tile_type.h \
    ../src/command_executor.h \
    ../src/engine.h

FORMS    += MapEditor.ui
