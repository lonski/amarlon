#ifndef DIRECTIONSELECTOR_H
#define DIRECTIONSELECTOR_H

#include <libtcod.hpp>

namespace amarlon {

class DirectionSelector
{
public:
  DirectionSelector();
  TCOD_key_t select(int& dx, int& dy);

};

}

#endif // DIRECTIONSELECTOR_H
