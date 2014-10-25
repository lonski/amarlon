TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++0x -g -Wall -Wextra -Wformat-security

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

INCLUDEPATH += $$PWD/../include/libtcod
DEPENDPATH += $$PWD/../include/libtcod

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

win32: LIBS += -L$$PWD/../lib/ -ltcod-mingw -lgtest
unix: LIBS += -L$$PWD/../lib/ -ltcod -ltcodxx -lgtest

SOURCES += \
    ActorTest.cpp \
    CommandExecutorTest.cpp \
    main.cpp \
    UtilsTest.cpp \
    DataGateway/DataGatewayTest.cpp \
    DataGateway/MapGatewayTest.cpp \
    World/MapTest.cpp \
    ../src/Actor/Actor.cpp \
    ../src/Actor/ActorFeatures/ActorFeature.cpp \
    ../src/Actor/ActorFeatures/Container.cpp \
    ../src/Actor/ActorFeatures/Fighter.cpp \
    ../src/Actor/ActorFeatures/Pickable.cpp \
    ../src/Actor/ActorFeatures/Ai/Ai.cpp \
    ../src/Actor/ActorFeatures/Ai/MonsterAi.cpp \
    ../src/Actor/ActorFeatures/Openable/Openable.cpp \
    ../src/Actor/ActorFeatures/Openable/OpenableContainer.cpp \
    ../src/Actor/ActorFeatures/Openable/OpenableDoor.cpp \
    ../src/Actor/Effects/Effect.cpp \
    ../src/Actor/Effects/LockEffect.cpp \
    ../src/Actor/Effects/SelfHealEffect.cpp \
    ../src/DataGateways/ActorDB.cpp \
    ../src/DataGateways/DataGateway.cpp \
    ../src/DataGateways/MapGateway.cpp \
    ../src/DataGateways/TileDB.cpp \
    ../src/DataGateways/Parsers/ActorParser.cpp \
    ../src/World/Map.cpp \
    ../src/Utils/DirectionSelector.cpp \
    ../src/Utils/InventoryManager.cpp \
    ../src/Utils/ItemPicker.cpp \
    ../src/Utils/Messenger.cpp \
    ../src/Utils/Utils.cpp \
    ../src/Utils/TargetSelector/ExecutorSelector.cpp \
    ../src/Utils/TargetSelector/SingleNeighbourSelector.cpp \
    ../src/Utils/TargetSelector/TargetSelector.cpp \
    ../src/Commands/CmdClose.cpp \
    ../src/Commands/CmdDrop.cpp \
    ../src/Commands/CmdFullscreen.cpp \
    ../src/Commands/CmdInventory.cpp \
    ../src/Commands/CmdMove.cpp \
    ../src/Commands/CmdOpen.cpp \
    ../src/Commands/CmdPick.cpp \
    ../src/Commands/CmdUse.cpp \
    ../src/Commands/Command.cpp \
    ../src/Gui/AmountWindow.cpp \
    ../src/Gui/Gui.cpp \
    ../src/Gui/ItemPickerWindow.cpp \
    ../src/CommandExecutor.cpp \
    ../src/Engine.cpp \
    ../src/Gui/Widget/bar.cpp \
    ../src/Gui/Widget/list.cpp \
    ../src/Gui/Widget/panel.cpp \
    ../src/Gui/Widget/widget.cpp \
    ../src/Gui/Widget/label.cpp


HEADERS += \
    ../src/World/Map.h \
    ../src/Actor/Actor.h \
    ../src/Actor/ActorType.h \
    ../src/Actor/ActorFeatures/ActorFeature.h \
    ../src/Actor/ActorFeatures/Container.h \
    ../src/Actor/ActorFeatures/Fighter.h \
    ../src/Actor/ActorFeatures/Pickable.h \
    ../src/Actor/ActorFeatures/Ai/Ai.h \
    ../src/Actor/ActorFeatures/Ai/AiType.h \
    ../src/Actor/ActorFeatures/Ai/MonsterAi.h \
    ../src/Actor/ActorFeatures/Openable/Openable.h \
    ../src/Actor/ActorFeatures/Openable/OpenableContainer.h \
    ../src/Actor/ActorFeatures/Openable/OpenableDoor.h \
    ../src/Actor/ActorFeatures/Openable/OpenableType.h \
    ../src/Actor/Effects/Effect.h \
    ../src/Actor/Effects/EffectType.h \
    ../src/Actor/Effects/LockEffect.h \
    ../src/Actor/Effects/SelfHealEffect.h \
    ../src/DataGateways/ActorDB.h \
    ../src/DataGateways/ActorDescriptions.h \
    ../src/DataGateways/DataGateway.h \
    ../src/DataGateways/MapGateway.h \
    ../src/DataGateways/TileDB.h \
    ../src/DataGateways/Parsers/ActorParser.h \
    ../src/World/Map.h \
    ../src/World/MapId.h \
    ../src/World/TileType.h \
    ../src/Utils/DirectionSelector.h \
    ../src/Utils/glodef.h \
    ../src/Utils/InventoryManager.h \
    ../src/Utils/ItemPicker.h \
    ../src/Utils/LogEntry.h \
    ../src/Utils/Messenger.h \
    ../src/Utils/SelectorType.h \
    ../src/Utils/Utils.h \
    ../src/Utils/XmlUtils.h \
    ../src/Utils/TargetSelector/ExecutorSelector.h \
    ../src/Utils/TargetSelector/SingleNeighbourSelector.h \
    ../src/Utils/TargetSelector/TargetSelector.h \
    ../src/Commands/CmdClose.h \
    ../src/Commands/CmdDrop.h \
    ../src/Commands/CmdFullscreen.h \
    ../src/Commands/CmdInventory.h \
    ../src/Commands/CmdMove.h \
    ../src/Commands/CmdOpen.h \
    ../src/Commands/CmdPick.h \
    ../src/Commands/CmdUse.h \
    ../src/Commands/Command.h \
    ../src/Gui/AmountWindow.h \
    ../src/Gui/Gui.h \
    ../src/Gui/ItemPickerWindow.h \
    ../src/CommandExecutor.h \
    ../src/Engine.h \
    ../src/Gui/Widget/bar.h \
    ../src/Gui/Widget/list.h \
    ../src/Gui/Widget/panel.h \
    ../src/Gui/Widget/widget.h \
    ../src/Gui/Widget/label.h

