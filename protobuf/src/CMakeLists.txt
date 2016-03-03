set(HEADER_FILES
    spell.pb.h
)

set(SOURCE_FILES
    spell.pb.cc
)

add_library(proto_data SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(proto_data ${PROTOBUF_LIBRARIES})

