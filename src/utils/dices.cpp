#include "dices.h"
#include <libtcod.hpp>

namespace amarlon { namespace dices {

int roll(int from, int to)
{
  return TCODRandom::getInstance()->getInt(from, to );
}

int roll(Die dieType)
{
  return roll(1, static_cast<int>(dieType) );
}

}}
