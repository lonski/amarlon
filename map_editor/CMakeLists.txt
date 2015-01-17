set(HEADER_FILES
    map_editor.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/ai/ai.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/ai/ai_type.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/ai/monster_ai.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/openable/openable.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/openable/openable_container.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/openable/openable_door.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/openable/openable_type.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/wearer/item_slot_type.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/wearer/wearer.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/actor_feature.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/container.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/fighter.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/pickable.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorFeatures/pickable_category.h
    ${PROJECT_SOURCE_DIR}/src/Actor/Effects/Effect.h
    ${PROJECT_SOURCE_DIR}/src/Actor/Effects/EffectType.h
    ${PROJECT_SOURCE_DIR}/src/Actor/Effects/LockEffect.h
    ${PROJECT_SOURCE_DIR}/src/Actor/Effects/SelfHealEffect.h
    ${PROJECT_SOURCE_DIR}/src/Actor/Actor.h
    ${PROJECT_SOURCE_DIR}/src/Actor/ActorType.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_put_into.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_close.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_fullscreen.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_help.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_inventory.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_move.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_open.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_pick.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_use.h
    ${PROJECT_SOURCE_DIR}/src/commands/cmd_look.h
    ${PROJECT_SOURCE_DIR}/src/commands/command.h
    ${PROJECT_SOURCE_DIR}/src/DataGateways/Parsers/ActorParser.h
    ${PROJECT_SOURCE_DIR}/src/DataGateways/Parsers/parser.h
    ${PROJECT_SOURCE_DIR}/src/DataGateways/Parsers/map_parser.h
    ${PROJECT_SOURCE_DIR}/src/DataGateways/Parsers/tile_parser.h
    ${PROJECT_SOURCE_DIR}/src/DataGateways/serializers/serializer.h
    ${PROJECT_SOURCE_DIR}/src/DataGateways/serializers/map_serializer.h
    ${PROJECT_SOURCE_DIR}/src/DataGateways/ActorDB.h
    ${PROJECT_SOURCE_DIR}/src/DataGateways/ActorDescriptions.h
    ${PROJECT_SOURCE_DIR}/src/DataGateways/MapGateway.h
    ${PROJECT_SOURCE_DIR}/src/DataGateways/TileDB.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/menu/items_menu.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/menu/label_menu_item.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/menu/menu.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/menu/menu_item.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/menu/slot_menu_item.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/bar.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/label.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/list.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/panel.h
    ${PROJECT_SOURCE_DIR}/src/gui/widget/widget.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/inventory_window/bag_manager.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/inventory_window/body_manager.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/inventory_window/inventory_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/text_window/resizeable_text_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/text_window/text_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/amount_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/pick_up_window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/window.h
    ${PROJECT_SOURCE_DIR}/src/gui/window/window_manager.h
    ${PROJECT_SOURCE_DIR}/src/gui/gui.h
    ${PROJECT_SOURCE_DIR}/src/gui/message_box.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_selector/executor_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_selector/single_neighbour_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/target_selector/target_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/amarlon_except.h
    ${PROJECT_SOURCE_DIR}/src/utils/colored_string.h
    ${PROJECT_SOURCE_DIR}/src/utils/configuration.h
    ${PROJECT_SOURCE_DIR}/src/utils/direction_selector.h
    ${PROJECT_SOURCE_DIR}/src/utils/item_picker.h
    ${PROJECT_SOURCE_DIR}/src/utils/messenger.h
    ${PROJECT_SOURCE_DIR}/src/utils/selector_type.h
    ${PROJECT_SOURCE_DIR}/src/utils/singleton.h
    ${PROJECT_SOURCE_DIR}/src/utils/utils.h
    ${PROJECT_SOURCE_DIR}/src/utils/xml_utils.h
    ${PROJECT_SOURCE_DIR}/src/world/map.h
    ${PROJECT_SOURCE_DIR}/src/world/map_id.h
    ${PROJECT_SOURCE_DIR}/src/world/tile_type.h
    ${PROJECT_SOURCE_DIR}/src/command_executor.h
    ${PROJECT_SOURCE_DIR}/src/engine.h
    )

set(SOURCE_FILES
    main.cpp
    map_editor.cpp
    )

find_package(Qt4 REQUIRED)
include(${QT_USE_FILE})

set(MAP_EDITOR_UI
    ${PROJECT_SOURCE_DIR}/map_editor/map_editor.ui
    )

set(MAP_EDITOR_QT
    ${PROJECT_SOURCE_DIR}/map_editor/map_editor.h
    )

qt4_wrap_ui(MAP_EDITOR_UI_HDR ${MAP_EDITOR_UI})
qt4_wrap_cpp(MAP_EDITOR_MOC_SRC ${MAP_EDITOR_QT})

include_directories(${CMAKE_CURRENT_BINARY_DIR})

add_executable(mapeditor ${SOURCE_FILES} ${HEADER_FILES} ${MAP_EDITOR_UI_HDR} ${MAP_EDITOR_MOC_SRC})
target_link_libraries(mapeditor amarlon_core ${TCOD_LIBRARIES} ${QT_LIBRARIES})

add_custom_command(TARGET mapeditor POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/resources $<TARGET_FILE_DIR:mapeditor>)
