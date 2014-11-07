cmake_minimum_required(VERSION 2.8.4)
project(amarlon)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)
find_package(tcod HINTS "${PROJECT_SOURCE_DIR}" REQUIRED)
include_directories(${TCOD_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -O2 -Wall -Wextra -Wformat-security -pipe -march=native -mtune=native")

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(${PROJECT_SOURCE_DIR}/Actor)
include_directories(${PROJECT_SOURCE_DIR}/Actor/ActorFeatures)
include_directories(${PROJECT_SOURCE_DIR}/Actor/Effects)
include_directories(${PROJECT_SOURCE_DIR}/Commands)
include_directories(${PROJECT_SOURCE_DIR}/DataGateways)
include_directories(${PROJECT_SOURCE_DIR}/DataGateways/Parsers)
include_directories(${PROJECT_SOURCE_DIR}/Gui)
include_directories(${PROJECT_SOURCE_DIR}/Gui/Widget)
include_directories(${PROJECT_SOURCE_DIR}/Utils)
include_directories(${PROJECT_SOURCE_DIR}/Utils/TargetSelector)
include_directories(${PROJECT_SOURCE_DIR}/World)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${amarlon_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${amarlon_BINARY_DIR}")

add_subdirectory(src)
add_subdirectory(test)
