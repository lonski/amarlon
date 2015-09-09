#ifndef TILE_H
#define TILE_H

#include <memory>
#include <vector>
#include <stdint.h>
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
  uint8_t type;
  uint8_t flags;
  uint8_t x;
  uint8_t y;
  uint8_t reserverd[4];
};

struct Tile
{
  constexpr static int defaultMonsterRenderPriority = 10;
  constexpr static int defaultItemRenderPriority = 20;

  Tile(uint32_t x = 0, uint32_t y = 0);
  Tile(const Tile& tile);
  Tile& operator=(const Tile& rhs);

  // Instead of vector mainly because of 'add' function - managing actor stacking
  // TODO: Refactor to use rather a vector and Tile::add function
  ContainerPtr actors;

  //TODO: Rethink if the coords should be here here.
  //      How to remove it and deserialize tiles?
  //      Maybe serialize each row separately in xml?
  uint32_t x;
  uint32_t y;

  bool isWalkable() const;
  bool isTransparent() const;
  bool isExplored() const;
  void setExplored(bool explored);
  TileType getType() const;

  /**
   * @return The tile color, basing on the Tile DB
   */
  TCODColor getColor();

  /**
   * @return The character representing this tile, basing on the Tile DB
   */
  char getChar();

  /**
   * @return Returns Actor with the highest tile render piority
   */
  ActorPtr top(std::function<bool(ActorPtr)> filterFun = [](ActorPtr){return true;} );

  std::vector<unsigned char> serialize();
  void deserialize(const SerializedTile& t);

private:
  uint8_t _flags;
  TileType _type;

};

}

#endif // TILE_H
