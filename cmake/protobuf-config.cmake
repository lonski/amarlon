if(PROTOBUF_LIBRARIES)
    # it's in cache already
    set(PROTOBUF_FOUND TRUE)
else(PROTOBUF_LIBRARIES)

    find_library(PROTOBUF_LIBRARY
      NAMES
        protobuf
        libprotobuf
      PATHS
          "${CMAKE_CURRENT_SOURCE_DIR}/lib"
          "${PROJECT_SOURCE_DIR}/lib"
    )

    set(PROTOBUF_LIBRARIES ${PROTOBUF_LIBRARIES} ${PROTOBUF_LIBRARY} )

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(protobuf DEFAULT_MSG PROTOBUF_LIBRARIES)

    # show the PROTOBUF_LIBRARIES variables only in the advanced view
    mark_as_advanced(PROTOBUF_LIBRARIES)

endif(PROTOBUF_LIBRARIES)
