#include "dices.h"
#include <random>
#include <libtcod.hpp>

namespace amarlon { namespace dices {

int roll(int from, int to)
{
//  std::random_device rd;
//  std::mt19937 mt(rd());
//  std::uniform_int_distribution<int> dist(from, to);

//  return dist(mt);

  return TCODRandom::getInstance()->getInt(from, to);
}

int roll(Dice diceType)
{
  return roll(1, static_cast<int>(diceType) );
}

int roll(Dice diceType, int n)
{
  int r = 0;

  if ( diceType != dices::NoDice )
  {
    for ( int c = 0; c < n; ++c)
    {
      r += dices::roll( diceType );
    }
  }

  return r;
}

}}

