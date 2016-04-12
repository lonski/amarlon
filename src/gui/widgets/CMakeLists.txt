set(HEADER_FILES
    awidget.h
    alabel.h
    alist.h
    apanel.h
    abar.h
    amenu_item.h
    alabel_menu_item.h
    aslot_menu_item.h
    amenu.h
    asub_panel.h
    ahorizontal_menu.h
    apanel_button.h
    atext_edit.h
)

set(SOURCE_FILES
    awidget.cpp
    alabel.cpp
    alist.cpp
    apanel.cpp
    abar.cpp
    alabel_menu_item.cpp
    aslot_menu_item.cpp
    amenu.cpp
    ahorizontal_menu.cpp
    apanel_button.cpp
    atext_edit.cpp
)

add_library(a_widgets SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(a_widgets ${TCOD_LIBRARIES})
