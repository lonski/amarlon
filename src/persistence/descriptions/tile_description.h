#ifndef TILE_DESCRIPTION_H
#define TILE_DESCRIPTION_H

#include <description.h>

namespace amarlon {

struct TileDescription : Description
{
  int type;
  char character;
  std::string color;
  bool walkable;
  bool transparent;
};

}

#endif // TILE_DESCRIPTION_H
