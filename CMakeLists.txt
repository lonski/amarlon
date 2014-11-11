cmake_minimum_required(VERSION 2.8.4)
project(amarlon)

set(amarlon_BINARY_DIR ${PROJECT_SOURCE_DIR}/build/)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
find_package(tcod HINTS "${PROJECT_SOURCE_DIR}" REQUIRED)
include_directories(${TCOD_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -O2 -Wall -Wextra -Wformat-security -pipe")

include_directories(${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src
    ${PROJECT_SOURCE_DIR}/Actor
    ${PROJECT_SOURCE_DIR}/Actor/ActorFeatures
    ${PROJECT_SOURCE_DIR}/Actor/Effects
    ${PROJECT_SOURCE_DIR}/Commands
    ${PROJECT_SOURCE_DIR}/DataGateways
    ${PROJECT_SOURCE_DIR}/DataGateways/Parsers
    ${PROJECT_SOURCE_DIR}/gui
    ${PROJECT_SOURCE_DIR}/gui/widget
    ${PROJECT_SOURCE_DIR}/gui/widget/window
    ${PROJECT_SOURCE_DIR}/gui/widget/window/inventory_window
    ${PROJECT_SOURCE_DIR}/utils
    ${PROJECT_SOURCE_DIR}/utils/target_selector
    ${PROJECT_SOURCE_DIR}/world)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${amarlon_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${amarlon_BINARY_DIR}")

add_subdirectory(src)
add_subdirectory(test)
