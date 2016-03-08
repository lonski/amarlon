#ifndef TILE_H
#define TILE_H

#include <memory>
#include <vector>
#include <stdint.h>
#include <tile_type.h>
#include <libtcod.hpp>
#include <tile.pb.h>

namespace amarlon {

class ActorContainer;
class Map;
class Actor;
typedef std::shared_ptr<ActorContainer> ActorContainerPtr;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<TileData> TileDataPtr;

struct Tile
{
  constexpr static int defaultMonsterRenderPriority = 10;
  constexpr static int defaultItemRenderPriority = 20;

  Tile();
  Tile(const TileState& state);
  Tile(const Tile& tile);
  Tile& operator=(const Tile& rhs);

  void setState(const TileState& state);
  const TileState& getState() const;

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

private:
  TileDataPtr _data;
  TileState   _state;

  ActorContainerPtr _actors;
};

}

#endif // TILE_H
