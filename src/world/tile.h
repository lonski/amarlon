#ifndef TILE_H
#define TILE_H

#include <memory>
#include <vector>
#include <tile_type.h>
#include <libtcod.hpp>

namespace amarlon {

class Container;
class Map;
class Actor;
typedef std::shared_ptr<Container> ContainerPtr;
typedef std::shared_ptr<Actor> ActorPtr;

struct SerializedTile
{
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

  // instead of vector mainly because of 'add' function - managing actor stacking
  // TODO: refactor to use rather a vector and Tile::add function
  ContainerPtr actors;
  uint32_t x;
  uint32_t y;

  Tile(uint32_t x = 0, uint32_t y = 0);
  Tile(const Tile& tile);
  Tile& operator=(const Tile& rhs);

  std::vector<unsigned char> serialize();
  void deserialize(const SerializedTile& t);

  /**
   * @return Returns Actor with the highest tile render piority
   */
  ActorPtr top(std::function<bool(ActorPtr)> filterFun = [](ActorPtr){return true;} );

  /**
   * @return The tile color, basing on the Tile DB
   */
  TCODColor getColor();

  /**
   * @return The character representing this tile, basing on the Tile DB
   */
  char getChar();

  bool isWalkable() const;
  bool isTransparent() const;

};

}

#endif // TILE_H
