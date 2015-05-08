if(GTEST_LIBRARIES AND GTEST_INCLUDE_DIRS)
    # it's in cache already
    set(GTEST_FOUND TRUE)
else(GTEST_LIBRARIES AND GTEST_INCLUDE_DIRS)
    find_path(GTEST_INCLUDE_DIR
	NAMES gtest/gtest.h
	PATHS
	    /usr/include
	    /usr/local/include
	    /opt/local/include
	    "${CMAKE_CURRENT_SOURCE_DIR}/include"
	    "${PROJECT_SOURCE_DIR}/include"
    )
    set(GTEST_INCLUDE_DIRS ${GTEST_INCLUDE_DIR} "${GTEST_INCLUDE_DIR}/gtest")

    find_library(GTEST_CXX_LIBRARY
	NAMES
	    GTest
		libgtest
		libgtest_main
	PATHS
	    /usr/lib
	    /usr/local/lib
	    /opt/local/lib
	    "${CMAKE_CURRENT_SOURCE_DIR}/lib"
	    "${PROJECT_SOURCE_DIR}/lib"
    )
	
    set(GTEST_LIBRARIES ${GTEST_LIBRARIES} ${GTEST_CXX_LIBRARY})

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(libgtest DEFAULT_MSG GTEST_LIBRARIES GTEST_INCLUDE_DIRS)

    # show the GTEST_INCLUDE_DIRS and GTEST_LIBRARIES variables only in the advanced view
    mark_as_advanced(GTEST_INCLUDE_DIRS GTEST_LIBRARIES)

endif(GTEST_LIBRARIES AND GTEST_INCLUDE_DIRS)
