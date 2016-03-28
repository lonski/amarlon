set(HEADER_FILES
    spell.pb.h
    skill.pb.h
    tile.pb.h
    actor.pb.h
    drop_rule.pb.h
    item_type.pb.h
    utils.pb.h
)

set(SOURCE_FILES
    spell.pb.cc
    skill.pb.cc
    tile.pb.cc
    actor.pb.cc
    drop_rule.pb.cc
    item_type.pb.cc
    utils.pb.cc
)

add_library(proto_data SHARED ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(proto_data ${PROTOBUF_LIBRARIES})

