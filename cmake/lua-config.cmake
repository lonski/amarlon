if(LUA_LIBRARIES AND LUA_INCLUDE_DIRS)
    # it's in cache already
    set(LUA_FOUND TRUE)
else(LUA_LIBRARIES AND LUA_INCLUDE_DIRS)
    find_path(LUA_INCLUDE_DIR
	NAMES 
		lua.h
		lua/lua.h
	PATHS
      "${CMAKE_CURRENT_SOURCE_DIR}/include/lua"
      "${PROJECT_SOURCE_DIR}/include/lua"
      /usr/include/lua
      /usr/include/lua5.2
      /usr/local/include
      /usr/local/include/lua5.2
      /opt/local/include
      /opt/local/include/lua5.2
    )
    set(LUA_INCLUDE_DIRS ${LUA_INCLUDE_DIR} "${LUA_INCLUDE_DIR}" )

    find_library(LUA_CXX_LIBRARY
	NAMES
	    lua
	    liblua
	    liblua5.2
	PATHS
	    /usr/lib
	    /usr/local/lib
	    /opt/local/lib
	    /usr/lib/i386-linux-gnu/
	    /usr/lib/i686-linux-gnu/
	    "${CMAKE_CURRENT_SOURCE_DIR}/lib"
	    "${PROJECT_SOURCE_DIR}/lib"
    )
	
    set(LUA_LIBRARIES ${LUA_LIBRARIES} ${LUA_CXX_LIBRARY})

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(liblua DEFAULT_MSG LUA_LIBRARIES LUA_INCLUDE_DIRS)

    # show the LUA_INCLUDE_DIRS and LUA_LIBRARIES variables only in the advanced view
    mark_as_advanced(LUA_INCLUDE_DIRS LUA_LIBRARIES)

endif(LUA_LIBRARIES AND LUA_INCLUDE_DIRS)
