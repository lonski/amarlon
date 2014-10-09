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
    utils.cpp \
    DataGateways/TileDB.cpp \
    CommandExecutor.cpp \
    Actor/actor.cpp \
    Commands/command.cpp \
    Commands/CmdMove.cpp \
    DataGateways/ActorDB.cpp \
    Commands/CmdOpen.cpp \
    Commands/CmdFullscreen.cpp

HEADERS += \
    DataGateways/DataGateway.h \
    World/map.h \
    DataGateways/MapGateway.h \
    World/MapId.h \
    World/TileType.h \
    engine.h \
    utils.h \
    DataGateways/TileDB.h \
    CommandExecutor.h \
    Actor/actor.h \
    Commands/command.h \
    Commands/CmdMove.h \
    DataGateways/ActorDB.h \
    Actor/ActorType.h \
    Commands/CmdOpen.h \
    Commands/CmdFullscreen.h


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lib/ -ltcod-mingw
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lib/ -ltcod-mingw

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../include/libtcod
DEPENDPATH += $$PWD/../include
