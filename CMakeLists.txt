cmake_minimum_required(VERSION 2.8.4)
project(amarlon)

set(amarlon_BINARY_DIR ${PROJECT_SOURCE_DIR}/build/)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/)

include(amarlon_macros)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -g -O2 -Wall -Wextra -Wformat-security -pipe")

find_package(tcod HINTS "${PROJECT_SOURCE_DIR}" REQUIRED)
include_directories(${TCOD_INCLUDE_DIRS})

header_dirs("${PROJECT_SOURCE_DIR}/src" AMARLON_HEADER_DIRS)

include_directories(${AMARLON_HEADER_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${amarlon_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${amarlon_BINARY_DIR}")

add_subdirectory(src)
#add_subdirectory(test)
#add_subdirectory(map_editor)
