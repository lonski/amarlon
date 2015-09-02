#ifndef TILE_H
#define TILE_H

#include <memory>
#include <string>
#include <vector>
#include <tile_type.h>
#include <iostream>

namespace amarlon {

class Container;
class Map;
typedef std::shared_ptr<Container> ContainerPtr;

struct SerializedTile
{
  SerializedTile()
    : explored(false)
    , type(0)
    , x(0)
    , y(0)
  {}

  bool explored;
  int type;
  uint32_t x;
  uint32_t y;
};

struct Tile
{
  constexpr static int defaultMonsterRenderPriority = 10;
  constexpr static int defaultItemRenderPriority = 20;

  bool explored;
  TileType type;
  ContainerPtr actors;
  uint32_t x;
  uint32_t y;

  Tile(uint32_t x = 0, uint32_t y = 0);
  Tile(const Tile& tile);
  Tile& operator=(const Tile& rhs);

  void update(Map *map);
  std::vector<unsigned char> serialize();
  void deserialize(const SerializedTile& t);

};

}

#endif // TILE_H
