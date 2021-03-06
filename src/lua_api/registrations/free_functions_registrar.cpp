#include "free_functions_registrar.h"
#include <lua_state.h>
#include <message_box.h>
#include <dices.h>
#include <utils.h>

namespace amarlon {

void log(std::string msg)
{
  printf("%s\n", msg.c_str());
}

void msg(std::string msg)
{
  gui::msgBox(msg);
}

namespace lua_api {

void FreeFunctionRegistrar::reg(lua_State* state)
{
  using namespace luabind;

  module(state)
  [
      def("log", &log),
      def("msg", &msg),
      def("rollDice",  (int(*)(dices::Dice))&dices::roll ),
      def("rollDiceN", (int(*)(dices::Dice, int))&dices::roll ),
      def("calculateDistance", (float(*)(ActorPtr, ActorPtr))&calculateDistance )

  ];
}

}}
