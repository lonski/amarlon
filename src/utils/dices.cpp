#include "dices.h"
#include <libtcod.hpp>

namespace amarlon { namespace dices {

int roll(int from, int to)
{
  return TCODRandom::getInstance()->getInt(from, to );
}

int roll(Dice diceType)
{
  return roll(1, static_cast<int>(diceType) );
}

int roll(Dice diceType, int n)
{
  int r = 0;

  for ( int c = 0; c < n; ++c)
  {
    r += dices::roll( diceType );
  }

  return r;
}

}}
