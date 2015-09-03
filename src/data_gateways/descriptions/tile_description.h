#ifndef TILE_DESCRIPTION_H
#define TILE_DESCRIPTION_H

#include <libtcod.hpp>
#include <description.h>
#include <tile_type.h>

namespace amarlon {

struct TileDescription : Description
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
