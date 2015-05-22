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
)

add_library(amarlon_widgets STATIC ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(amarlon_widgets ${TCOD_LIBRARIES})