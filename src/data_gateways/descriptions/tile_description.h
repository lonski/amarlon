#ifndef TILE_DESCRIPTION_H
#define TILE_DESCRIPTION_H

#include <libtcod.hpp>
#include <world/tile_type.h>

namespace amarlon {

struct TileDescription
{
  TileType type;
  char character;
  char code;
  TCODColor color;
  bool walkable;
  bool transparent;
};

}

#endif // TILE_DESCRIPTION_H
