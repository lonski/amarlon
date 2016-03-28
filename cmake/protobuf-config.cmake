if(PROTOBUF_LIBRARIES AND PROTOBUF_INCLUDE_DIRS)
    # it's in cache already
    set(PROTOBUF_FOUND TRUE)
else(PROTOBUF_LIBRARIES AND PROTOBUF_INCLUDE_DIRS)

    find_library(PROTOBUF_LIBRARY
      NAMES
        protobuf
        libprotobuf
      PATHS
          "${CMAKE_CURRENT_SOURCE_DIR}/lib"
          "${PROJECT_SOURCE_DIR}/lib"
          /usr/local/lib
    )

  find_path(PROTOBUF_INCLUDE_DIR
      NAMES
        google/protobuf/message.h
      PATHS
          "${CMAKE_CURRENT_SOURCE_DIR}/include"
          "${PROJECT_SOURCE_DIR}/include"
    )

    set(PROTOBUF_LIBRARIES ${PROTOBUF_LIBRARIES} ${PROTOBUF_LIBRARY})
    set(PROTOBUF_INCLUDE_DIRS "${PROTOBUF_INCLUDE_DIR}")

    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(protobuf DEFAULT_MSG PROTOBUF_LIBRARIES PROTOBUF_INCLUDE_DIRS)

    # show the PROTOBUF_LIBRARIES variables only in the advanced view
    mark_as_advanced(PROTOBUF_LIBRARIES PROTOBUF_INCLUDE_DIRS)

endif(PROTOBUF_LIBRARIES AND PROTOBUF_INCLUDE_DIRS)