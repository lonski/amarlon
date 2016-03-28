if(LUABIND_LIBRARIES AND LUABIND_INCLUDE_DIRS)
    # it's in cache already
    set(LUABIND_FOUND TRUE)
else(LUABIND_LIBRARIES)

    find_path(LUABIND_INCLUDE_DIR
      NAMES
        luabind/luabind.hpp
      PATHS
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/include"
    )
    set(LUABIND_INCLUDE_DIRS ${LUABIND_INCLUDE_DIR} "${LUABIND_INCLUDE_DIR}/luabind")

    find_library(LUABIND_CXX_LIBRARY
      NAMES
        luabind09
        libluabind09
      PATHS
        "${CMAKE_CURRENT_SOURCE_DIR}/lib"
        "${PROJECT_SOURCE_DIR}/lib"
    )
	
    set(LUABIND_LIBRARIES ${LUABIND_LIBRARIES} ${LUABIND_CXX_LIBRARY})

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(libluabind09 DEFAULT_MSG LUABIND_LIBRARIES)

    # show the LUABIND_LIBRARIES variables only in the advanced view
    mark_as_advanced(LUABIND_LIBRARIES)

endif(LUABIND_LIBRARIES AND LUABIND_INCLUDE_DIRS)
