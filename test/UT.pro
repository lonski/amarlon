TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

unix:!macx|win32: LIBS += -L$$PWD/../lib/ -lgtest
win32: LIBS += -L$$PWD/../lib/ -ltcod-mingw

INCLUDEPATH += $$PWD/../include
INCLUDEPATH += $$PWD/../src
INCLUDEPATH += $$PWD/../src/Persistence
DEPENDPATH += $$PWD/../include
DEPENDPATH += $$PWD/../src
DEPENDPATH += $$PWD/../src/Persistence

SOURCES += main.cpp \
    DataGateway/DataGatewayTest.cpp \
    ../src/DataGateways/DataGateway.cpp \
    World/MapTest.cpp \
    ../src/World/map.cpp \
    DataGateway/MapGatewayTest.cpp \
    ../src/DataGateways/MapGateway.cpp \
    ../src/utils.cpp \
    UtilsTest.cpp \
    ../src/DataGateways/TileDB.cpp

HEADERS += \
    ../src/DataGateways/DataGateway.h \
    ../src/World/map.h \
    ../src/DataGateways/MapGateway.h \
    ../include/xml/rapidxml.hpp \
    ../include/xml/rapidxml_iterators.hpp \
    ../include/xml/rapidxml_print.hpp \
    ../include/xml/rapidxml_utils.hpp \
    ../src/utils.h \
    ../src/DataGateways/TileDB.h
