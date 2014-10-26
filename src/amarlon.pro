TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x -g -Wall -Wextra -Wformat-security

SOURCES += main.cpp \
    DataGateways/DataGateway.cpp \
    World/Map.cpp \
    DataGateways/MapGateway.cpp \
    DataGateways/TileDB.cpp \
    CommandExecutor.cpp \
    Actor/Actor.cpp \
    Commands/Command.cpp \
    Commands/CmdMove.cpp \
    DataGateways/ActorDB.cpp \
    Commands/CmdOpen.cpp \
    Commands/CmdFullscreen.cpp \
    Actor/ActorFeatures/Container.cpp \
    Commands/CmdInventory.cpp \
    Actor/ActorFeatures/Pickable.cpp \
    Commands/CmdPick.cpp \
    Utils/ItemPicker.cpp \
    Commands/CmdDrop.cpp \
    Utils/InventoryManager.cpp \
    Gui/Gui.cpp \
    Utils/Utils.cpp \
    Engine.cpp \
    Actor/ActorFeatures/ActorFeature.cpp \
    Actor/ActorFeatures/Fighter.cpp \
    Gui/ItemPickerWindow.cpp \
    Gui/AmountWindow.cpp \
    Commands/CmdClose.cpp \
    Utils/DirectionSelector.cpp \
    Actor/ActorFeatures/Openable/Openable.cpp \
    Actor/ActorFeatures/Openable/OpenableContainer.cpp \
    Actor/ActorFeatures/Openable/OpenableDoor.cpp \
    Actor/ActorFeatures/Ai/Ai.cpp \
    Actor/ActorFeatures/Ai/MonsterAi.cpp \
    Actor/Effects/Effect.cpp \
    Actor/Effects/LockEffect.cpp \
    Commands/CmdUse.cpp \
    Utils/TargetSelector/TargetSelector.cpp \
    Actor/Effects/SelfHealEffect.cpp \
    Utils/TargetSelector/ExecutorSelector.cpp \
    Utils/TargetSelector/SingleNeighbourSelector.cpp \
    DataGateways/Parsers/ActorParser.cpp \
    Utils/Messenger.cpp \
    Gui/Widget/widget.cpp \
    Gui/Widget/bar.cpp \
    Gui/Widget/panel.cpp \
    Gui/Widget/list.cpp \
    Gui/Widget/label.cpp \
    Actor/ActorFeatures/Wearer/wearer.cpp

HEADERS += \
    DataGateways/DataGateway.h \
    World/Map.h \
    DataGateways/MapGateway.h \
    World/MapId.h \
    World/TileType.h \
    Engine.h \
    DataGateways/TileDB.h \
    CommandExecutor.h \
    Actor/Actor.h \
    Commands/Command.h \
    Commands/CmdMove.h \
    DataGateways/ActorDB.h \
    Actor/ActorType.h \
    Commands/CmdOpen.h \
    Commands/CmdFullscreen.h \
    Actor/ActorFeatures/Container.h \
    Commands/CmdInventory.h \
    Actor/ActorFeatures/Pickable.h \
    Commands/CmdPick.h \
    Utils/ItemPicker.h \
    Commands/CmdDrop.h \
    Utils/InventoryManager.h \
    Gui/Gui.h \
    Utils/glodef.h \
    Utils/Utils.h \
    Actor/ActorFeatures/ActorFeature.h \
    Actor/ActorFeatures/Fighter.h \
    Gui/ItemPickerWindow.h \
    Gui/AmountWindow.h \
    Commands/CmdClose.h \
    Utils/DirectionSelector.h \
    Actor/ActorFeatures/Openable/Openable.h \
    Actor/ActorFeatures/Openable/OpenableContainer.h \
    Actor/ActorFeatures/Openable/OpenableDoor.h \
    Actor/ActorFeatures/Openable/OpenableType.h \
    Actor/ActorFeatures/Ai/Ai.h \
    Actor/ActorFeatures/Ai/AiType.h \
    Actor/ActorFeatures/Ai/MonsterAi.h \
    Actor/Effects/Effect.h \
    Actor/Effects/LockEffect.h \
    DataGateways/ActorDescriptions.h \
    Actor/Effects/EffectType.h \
    Utils/SelectorType.h \
    Commands/CmdUse.h \
    Utils/TargetSelector/TargetSelector.h \
    Actor/Effects/SelfHealEffect.h \
    Utils/TargetSelector/ExecutorSelector.h \
    Utils/TargetSelector/SingleNeighbourSelector.h \
    DataGateways/Parsers/ActorParser.h \
    Utils/XmlUtils.h \
    Utils/Messenger.h \
    Gui/Widget/widget.h \
    Gui/Widget/bar.h \
    Gui/Widget/panel.h \
    Gui/Widget/list.h \
    Utils/colored_string.h \
    Gui/Widget/label.h \
    Actor/ActorFeatures/Wearer/wearer.h \
    Actor/ActorFeatures/Wearer/item_slot_type.h


win32: LIBS += -L$$PWD/../lib/ -ltcod-mingw
unix:  LIBS += -L$$PWD/../lib/ -ltcod -ltcodxx

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../include/libtcod
DEPENDPATH += $$PWD/../include
