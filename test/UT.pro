TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include

INCLUDEPATH += $$PWD/../include/libtcod
DEPENDPATH += $$PWD/../include/libtcod

INCLUDEPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src

unix:!macx|win32: LIBS += -L$$PWD/../lib/ -lgtest
unix:!macx|win32: LIBS += -L$$PWD/../lib/ -ltcod-mingw

SOURCES += \
    ActorTest.cpp \
    CommandExecutorTest.cpp \
    main.cpp \
    UtilsTest.cpp \
    DataGateway/DataGatewayTest.cpp \
    DataGateway/MapGatewayTest.cpp \
    World/MapTest.cpp \
    ../src/World/map.cpp \
    ../src/DataGateways/ActorDB.cpp \
    ../src/DataGateways/DataGateway.cpp \
    ../src/DataGateways/MapGateway.cpp \
    ../src/DataGateways/TileDB.cpp \
    ../src/Actor/actor.cpp \
    ../src/Actor/ActorFeatures/ai.cpp \
    ../src/Actor/ActorFeatures/attacker.cpp \
    ../src/Actor/ActorFeatures/container.cpp \
    ../src/Actor/ActorFeatures/destrucible.cpp \
    ../src/Actor/ActorFeatures/MonsterAi.cpp \
    ../src/Actor/ActorFeatures/pickable.cpp \
    ../src/Gui/gui.cpp \
    ../src/Gui/ItemPickerGui.cpp

HEADERS += \
    ../src/World/map.h \
    ../src/World/MapId.h \
    ../src/World/TileType.h \
    ../src/DataGateways/ActorDB.h \
    ../src/DataGateways/DataGateway.h \
    ../src/DataGateways/MapGateway.h \
    ../src/DataGateways/TileDB.h \
    ../src/Actor/actor.h \
    ../src/Actor/ActorType.h \
    ../src/Actor/ActorFeatures/ai.h \
    ../src/Actor/ActorFeatures/AiType.h \
    ../src/Actor/ActorFeatures/attacker.h \
    ../src/Actor/ActorFeatures/container.h \
    ../src/Actor/ActorFeatures/destrucible.h \
    ../src/Actor/ActorFeatures/MonsterAi.h \
    ../src/Actor/ActorFeatures/pickable.h \
    ../src/Gui/gui.h \
    ../src/Gui/ItemPickerGui.h
