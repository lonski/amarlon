#include "animation_registrar.h"
#include <lua_state.h>
#include <blink.h>
#include <throw.h>
#include <expanding_circle.h>
#include <blinking_circle.h>
#include <converters.h>

namespace amarlon { namespace lua_api {

void AnimationRegistrar::reg(lua_State* state)
{
  using namespace luabind;
  module( state )
  [
      class_<animation::Blink, std::shared_ptr<animation::Blink> >("Blink")
        .def(constructor<TCODColor, int, int>())
        .def("setLocation", &animation::Blink::setLocation)
        .def("getStartLocation", &animation::Blink::getStartLocation)
        .def("getEndLocation", &animation::Blink::getEndLocation)
        .def("run", &animation::Blink::run),

      class_<animation::Throw, std::shared_ptr<animation::Throw> >("Throw")
        .def(constructor<TCODColor, char, int>())
        .def("setLocation", &animation::Throw::setLocation)
        .def("getStartLocation", &animation::Throw::getStartLocation)
        .def("getEndLocation", &animation::Throw::getEndLocation)
        .def("run", &animation::Throw::run),

      class_<animation::ExpandingCircle, std::shared_ptr<animation::ExpandingCircle> >("ExpandingCircle")
        .def(constructor<TCODColor, char, int, int>())
        .def("setLocation", &animation::ExpandingCircle::setLocation)
        .def("getStartLocation", &animation::ExpandingCircle::getStartLocation)
        .def("getEndLocation", &animation::ExpandingCircle::getEndLocation)
        .def("run", &animation::ExpandingCircle::run),

      class_<animation::BlinkingCircle, std::shared_ptr<animation::BlinkingCircle> >("BlinkingCircle")
        .def(constructor<TCODColor, int, int, int>())
        .def("setLocation", &animation::BlinkingCircle::setLocation)
        .def("getStartLocation", &animation::BlinkingCircle::getStartLocation)
        .def("getEndLocation", &animation::BlinkingCircle::getEndLocation)
        .def("run", &animation::BlinkingCircle::run)
  ];
}

}}
