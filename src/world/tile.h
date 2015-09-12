#ifndef TILE_H
#define TILE_H

#include <memory>
#include <vector>
#include <stdint.h>
#include <tile_type.h>
#include <libtcod.hpp>

namespace amarlon {

class ActorContainer;
class Map;
class Actor;
typedef std::shared_ptr<ActorContainer> ActorContainerPtr;
typedef std::shared_ptr<Actor> ActorPtr;

struct SerializedTile
{
  uint8_t type;
  uint8_t flags;
};

struct Tile
{
  constexpr static int defaultMonsterRenderPriority = 10;
  constexpr static int defaultItemRenderPriority = 20;

  Tile();
  Tile(const Tile& tile);
  Tile& operator=(const Tile& rhs);

  void addActor(ActorPtr actor);
  bool removeActor(ActorPtr actor);
  ActorContainer getActors( std::function<bool(ActorPtr)> filterFun = [](ActorPtr){return true;} );

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
  ActorContainerPtr _actors;
  uint8_t _flags;
  TileType _type;

};

}

#endif // TILE_H
