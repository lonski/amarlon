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
        .def("isExplored", (bool(Map::*)(int,int))&Map::isExplored)
        .def("isInFov", (bool(Map::*)(int,int))&Map::isInFov)
        .def("isBlocked", (bool(Map::*)(int,int))&Map::isBlocked)
        .def("isTransparent", (bool(Map::*)(int,int)const)&Map::isTransparent)
        .def("getActorsInRadius", (ActorVector(Map::*)(int,int,int)const)&Map::getActors)
        .def("getActors", (ActorVector(Map::*)()const)&Map::getActors)

  ];
}

}}

