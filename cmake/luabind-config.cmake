if(LUABIND_LIBRARIES)
    # it's in cache already
    set(LUABIND_FOUND TRUE)
else(LUABIND_LIBRARIES)

    find_library(LUABIND_CXX_LIBRARY
	NAMES
	    luabind
	    libluabind
	    libluabind09
	PATHS
      "${CMAKE_CURRENT_SOURCE_DIR}/lib"
      "${PROJECT_SOURCE_DIR}/lib"
	    /usr/lib
	    /usr/local/lib
	    /opt/local/lib
    )
	
    set(LUABIND_LIBRARIES ${LUABIND_LIBRARIES} ${LUABIND_CXX_LIBRARY})

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(libluabind DEFAULT_MSG LUABIND_LIBRARIES)

    # show the LUABIND_LIBRARIES variables only in the advanced view
    mark_as_advanced(LUABIND_LIBRARIES)

endif(LUABIND_LIBRARIES)
