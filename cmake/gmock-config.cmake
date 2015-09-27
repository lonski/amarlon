if(GMOCK_LIBRARIES AND GMOCK_INCLUDE_DIRS)
    # it's in cache already
    set(GMOCK_FOUND TRUE)
else(GMOCK_LIBRARIES AND GMOCK_INCLUDE_DIRS)

    find_path(GMOCK_INCLUDE_DIR
      NAMES gmock/gmock.h
      PATHS
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/include"
    )
    set(GMOCK_INCLUDE_DIRS ${GMOCK_INCLUDE_DIR} "${GMOCK_INCLUDE_DIR}/gmock")

    find_library(GMOCK_CXX_LIBRARY
      NAMES
        gmock
        libgmock
        libgmock_main
      PATHS
        "${CMAKE_CURRENT_SOURCE_DIR}/lib"
        "${PROJECT_SOURCE_DIR}/lib"
    )
	
    set(GMOCK_LIBRARIES ${GMOCK_LIBRARIES} ${GMOCK_CXX_LIBRARY})

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(libgmock DEFAULT_MSG GMOCK_LIBRARIES GMOCK_INCLUDE_DIRS)

    # show the GMOCK_INCLUDE_DIRS and GMOCK_LIBRARIES variables only in the advanced view
    mark_as_advanced(GMOCK_INCLUDE_DIRS GMOCK_LIBRARIES)

endif(GMOCK_LIBRARIES AND GMOCK_INCLUDE_DIRS)
