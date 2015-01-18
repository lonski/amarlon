find_package(GTest REQUIRED)

set(HEADER_FILES
    ${PROJECT_SOURCE_DIR}/src/actor/actor.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_type.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/actor_feature.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/container.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/fighter.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/pickable.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/ai/ai.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/ai/ai_type.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/ai/monster_ai.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/openable/openable.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/openable/openable_container.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/openable/openable_door.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/openable/openable_type.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/wearer/item_slot_type.h
    ${PROJECT_SOURCE_DIR}/src/actor/actor_features/wearer/wearer.h
    ${PROJECT_SOURCE_DIR}/src/actor/effects/effect.h
    ${PROJECT_SOURCE_DIR}/src/actor/effects/effect_type.h
    ${PROJECT_SOURCE_DIR}/src/actor/effects/lock_effect.h
    ${PROJECT_SOURCE_DIR}/src/actor/effects/self_heal_effect.h
    ${PROJECT_SOURCE_DIR}/src/data_gateways/actor_db.h
    ${PROJECT_SOURCE_DIR}/src/data_gateways/actor_descriptions.h
    ${PROJECT_SOURCE_DIR}/src/data_gateways/map_gateway.h
    ${PROJECT_SOURCE_DIR}/src/data_gateways/tile_db.h
    ${PROJECT_SOURCE_DIR}/src/data_gateways/parsers/actor_parser.h
    ${PROJECT_SOURCE_DIR}/src/data_gateways/parsers/parser.h
    ${PROJECT_SOURCE_DIR}/src/data_gateways/parsers/tile_parser.h
    ${PROJECT_SOURCE_DIR}/src/world/map.h
    ${PROJECT_SOURCE_DIR}/src/world/map_id.h
    ${PROJECT_SOURCE_DIR}/src/world/tile_type.h
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
    ${PROJECT_SOURCE_DIR}/src/gui/widget/bar.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/list.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/panel.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/widget.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/label.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/inventory_window/inventory_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/menu/label_menu_item.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/menu/menu_item.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/menu/menu.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/menu/slot_menu_item.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/text_window/text_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/text_window/resizeable_text_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/menu/items_menu.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/inventory_window/bag_manager.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/inventory_window/body_manager.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/pick_up_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/amount_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/gui.h
    ${PROJECT_SOURCE_DIR}/src/utils/direction_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/item_picker.h
    ${PROJECT_SOURCE_DIR}/src/utils/amarlon_except.h
#    ${PROJECT_SOURCE_DIR}/src/utils/LogEntry.h
    ${PROJECT_SOURCE_DIR}/src/utils/messenger.h
    ${PROJECT_SOURCE_DIR}/src/utils/selector_type.h
    ${PROJECT_SOURCE_DIR}/src/utils/utils.h
    ${PROJECT_SOURCE_DIR}/src/utils/xml_utils.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_selector/executor_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_selector/single_neighbour_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_selector/target_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_selector/single_range_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/configuration.h
    ${PROJECT_SOURCE_DIR}/src/data_gateways/parsers/map_parser.h
    ${PROJECT_SOURCE_DIR}/src/data_gateways/serializers/serializer.h
    ${PROJECT_SOURCE_DIR}/src/data_gateways/serializers/map_serializer.h
)

set(SOURCE_FILES
    main.cpp
    actor_test.cpp
    command_executor_test.cpp
    utils_test.cpp
    data_gateway/map_gateway_test.cpp
    world/map_test.cpp
    wearer_test.cpp
)

add_executable(ut_amarlon ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(ut_amarlon amarlon_core ${TCOD_LIBRARIES} ${GTEST_LIBRARIES})

add_custom_command(TARGET ut_amarlon POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:ut_amarlon>)
