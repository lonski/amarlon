find_package(gtest HINTS "${PROJECT_SOURCE_DIR}" REQUIRED)
find_package(gmock HINTS "${PROJECT_SOURCE_DIR}" REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
include_directories(${GMOCK_INCLUDE_DIRS})

set(HEADER_FILES
    ${PROJECT_SOURCE_DIR}/src/module.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor.h
    ${PROJECT_SOURCE_DIR}/src/actor/status_effects_manager.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/actor_feature.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/inventory/inventory.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/character/character.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/pickable/pickable.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/ai/ai.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/openable/openable.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/wearer/item_slot_type.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/wearer/wearer.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/destroyable/destroyable.h
    ${PROJECT_SOURCE_DIR}/src/databases/actor_db.h
    ${PROJECT_SOURCE_DIR}/src/persistence/descriptions/actor_descriptions.h
    ${PROJECT_SOURCE_DIR}/src/persistence/descriptions/description.h
    ${PROJECT_SOURCE_DIR}/src/persistence/descriptions/spell_description.h
    ${PROJECT_SOURCE_DIR}/src/databases/spell_db.h
    ${PROJECT_SOURCE_DIR}/src/databases/tile_db.h
    ${PROJECT_SOURCE_DIR}/src/databases/map_db.h
    ${PROJECT_SOURCE_DIR}/src/persistence/parsers/actor_parser.h
    ${PROJECT_SOURCE_DIR}/src/persistence/parsers/parser.h
    ${PROJECT_SOURCE_DIR}/src/persistence/parsers/tile_parser.h
    ${PROJECT_SOURCE_DIR}/src/world/map.h
    ${PROJECT_SOURCE_DIR}/src/world/tile_type.h
    ${PROJECT_SOURCE_DIR}/src/world/tile.h
    ${PROJECT_SOURCE_DIR}/src/command_executor.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_help.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_close.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_fullscreen.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_inventory.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_move.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_open.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_pick.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_use.h
    ${PROJECT_SOURCE_DIR}/src/commands/command.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_put_into.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_look.h
    ${PROJECT_SOURCE_DIR}/src/engine.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/inventory_window/inventory_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/text_window/text_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/text_window/resizeable_text_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/inventory_window/bag_manager.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/inventory_window/body_manager.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/pick_up_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/amount_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/gui.h
    ${PROJECT_SOURCE_DIR}/src/utils/direction_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/amarlon_except.h
    ${PROJECT_SOURCE_DIR}/src/utils/messenger.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_type.h
    ${PROJECT_SOURCE_DIR}/src/utils/utils.h
    ${PROJECT_SOURCE_DIR}/src/utils/xml_utils.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_selector/executor_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_selector/single_neighbour_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_selector/target_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_selector/single_range_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/configuration.h
    ${PROJECT_SOURCE_DIR}/src/utils/damage.h
    ${PROJECT_SOURCE_DIR}/src/persistence/parsers/map_parser.h
    ${PROJECT_SOURCE_DIR}/src/persistence/serializers/serializer.h
    ${PROJECT_SOURCE_DIR}/src/persistence/serializers/map_serializer.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_actions/actor_action.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_actions/move_action.h
    ${PROJECT_SOURCE_DIR}/src/rpg_system/saving_throws_table.h
    mock/map_mock.h
)

set(SOURCE_FILES
    main.cpp
    actor_test.cpp
    command_executor_test.cpp
    utils_test.cpp
    data_gateway/map_gateway_test.cpp
    world/map_test.cpp
    wearer_test.cpp
    amenu_test.cpp
    character_test.cpp
    destroyable_test.cpp
    move_action_test.cpp
    spell_test.cpp
    drop_action_test.cpp
    status_effects_manager_test.cpp
    pickable_test.cpp
    equip_test.cpp
    treasure_generator_test.cpp
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGTEST_HAS_PTHREAD=1 -DTESTING=1")

add_executable(ut_amarlon ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(ut_amarlon a_core a_widgets a_persistence ${TCOD_LIBRARIES} ${GTEST_LIBRARIES} ${LUABIND_LIBRARIES})

add_custom_command(TARGET ut_amarlon POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:ut_amarlon>)
