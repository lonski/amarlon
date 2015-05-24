#ifndef TILE_H
#define TILE_H

#include <memory>
#include <tile_type.h>

namespace amarlon {

class Container;
typedef std::shared_ptr<Container> ContainerPtr;

struct Tile
{
  constexpr static int defaultMonsterRenderPriority = 10;
  constexpr static int defaultItemRenderPriority = 20;

  bool explored;
  TileType type;
  ContainerPtr actors;

  Tile();
  Tile(const Tile& tile);
  Tile& operator=(const Tile& rhs);

};

}

#endif // TILE_H
