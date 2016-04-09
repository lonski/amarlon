set(HEADER_FILES
  ${PROJECT_SOURCE_DIR}/src/utils/configuration.h
  ${PROJECT_SOURCE_DIR}/src/utils/base64.h
  ${PROJECT_SOURCE_DIR}/src/databases/tile_db.h
  map_editor.h
  maps_database.h
  map_edit_panel.h
  map_view_panel.h
)

set(SOURCE_FILES
  main.cpp
  ${PROJECT_SOURCE_DIR}/src/utils/configuration.cpp
  ${PROJECT_SOURCE_DIR}/src/utils/base64.cpp
  ${PROJECT_SOURCE_DIR}/src/databases/tile_db.cpp
  map_editor.cpp
  maps_database.cpp
  map_edit_panel.cpp
  map_view_panel.cpp
)

add_library(a_mapeditor STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(a_mapeditor ${TCOD_LIBRARIES})

add_executable(map_editor main.cpp)
target_link_libraries(map_editor a_mapeditor a_widgets a_persistence ${TCOD_LIBRARIES})
