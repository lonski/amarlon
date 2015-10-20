#include "map_registrar.h"
#include <lua_state.h>
#include <map.h>

namespace amarlon { namespace lua_api {

typedef std::vector<ActorPtr> ActorVector;

void MapRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<MapPtr>("MapPtr")
        .def("get", &MapPtr::get),

      class_<ActorVector>("ActorVector")
        .def("at",   (ActorVector::reference(ActorVector::*)(ActorVector::size_type))&ActorVector::at)
        .def("size", &ActorVector::size),

      class_<Map>("Map")
        .def("isExplored", &Map::isExplored)
        .def("isInFov", &Map::isInFov)
        .def("isBlocked", &Map::isBlocked)
        .def("isTransparent", &Map::isTransparent)
        .def("getActors", (ActorVector(Map::*)(int,int,int))&Map::getActors)

  ];
}

}}

