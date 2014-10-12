TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    DataGateways/DataGateway.cpp \
    World/map.cpp \
    DataGateways/MapGateway.cpp \
    engine.cpp \
    DataGateways/TileDB.cpp \
    CommandExecutor.cpp \
    Actor/actor.cpp \
    Commands/command.cpp \
    Commands/CmdMove.cpp \
    DataGateways/ActorDB.cpp \
    Commands/CmdOpen.cpp \
    Commands/CmdFullscreen.cpp \
    Actor/ActorFeatures/container.cpp \
    Commands/CmdInventory.cpp \
    Actor/ActorFeatures/pickable.cpp \
    Commands/CmdPick.cpp \
    Utils/ItemPicker.cpp \
    Commands/CmdDrop.cpp \
    Utils/InventoryManager.cpp \
    Actor/ActorFeatures/destrucible.cpp \
    Actor/ActorFeatures/attacker.cpp \
    Actor/ActorFeatures/ai.cpp \
    Actor/ActorFeatures/MonsterAi.cpp \
    Gui/gui.cpp \
    Gui/ItemPickerGui.cpp \
    Utils/utils.cpp

HEADERS += \
    DataGateways/DataGateway.h \
    World/map.h \
    DataGateways/MapGateway.h \
    World/MapId.h \
    World/TileType.h \
    engine.h \
    DataGateways/TileDB.h \
    CommandExecutor.h \
    Actor/actor.h \
    Commands/command.h \
    Commands/CmdMove.h \
    DataGateways/ActorDB.h \
    Actor/ActorType.h \
    Commands/CmdOpen.h \
    Commands/CmdFullscreen.h \
    Actor/ActorFeatures/container.h \
    Commands/CmdInventory.h \
    Actor/ActorFeatures/pickable.h \
    Commands/CmdPick.h \
    Utils/ItemPicker.h \
    Commands/CmdDrop.h \
    Utils/InventoryManager.h \
    Actor/ActorFeatures/destrucible.h \
    Actor/ActorFeatures/attacker.h \
    Actor/ActorFeatures/ai.h \
    Actor/ActorFeatures/MonsterAi.h \
    Actor/ActorFeatures/AiType.h \
    Gui/gui.h \
    Gui/ItemPickerGui.h \
    Utils/glodef.h \
    Utils/utils.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/ -ltcod-mingw
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/ -ltcod-mingw

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../include/libtcod
DEPENDPATH += $$PWD/../include
