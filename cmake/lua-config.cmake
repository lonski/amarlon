if(LUA_LIBRARIES AND LUA_INCLUDE_DIRS)
    # it's in cache already
    set(LUA_FOUND TRUE)
else(LUA_LIBRARIES AND LUA_INCLUDE_DIRS)
    find_path(LUA_INCLUDE_DIR
	NAMES 
		lua.h
	PATHS
      "${CMAKE_CURRENT_SOURCE_DIR}/include/lua"
      "${PROJECT_SOURCE_DIR}/include/lua"
	  PATH_SUFFIXES include/lua52 include/lua5.2 include/lua include lua
	  $ENV{LUA_DIR}
	  PATHS
    )
    set(LUA_INCLUDE_DIRS ${LUA_INCLUDE_DIR} "${LUA_INCLUDE_DIR}" )

    find_library(LUA_CXX_LIBRARY
	NAMES
	    lua
	    lua52
	    lua5.2
	    lua-5.2
	PATHS
	    PATH_SUFFIXES lib64 lib
	    $ENV{LUA_DIR}
	    PATHS
	    "${CMAKE_CURRENT_SOURCE_DIR}/lib"
	    "${PROJECT_SOURCE_DIR}/lib"
    )
	
    set(LUA_LIBRARIES ${LUA_LIBRARIES} ${LUA_CXX_LIBRARY})

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(liblua DEFAULT_MSG LUA_LIBRARIES LUA_INCLUDE_DIRS)

    # show the LUA_INCLUDE_DIRS and LUA_LIBRARIES variables only in the advanced view
    mark_as_advanced(LUA_INCLUDE_DIRS LUA_LIBRARIES)

endif(LUA_LIBRARIES AND LUA_INCLUDE_DIRS)
