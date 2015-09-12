#ifndef MAP_H
#define MAP_H

#include <vector>
#include <functional>
#include <memory>
#include <map>
#include <stdexcept>
#include <libtcod.hpp>
#include <map_id.h>
#include <directions.h>

namespace amarlon {

typedef unsigned int u32;

class Actor;
class ActorAction;
class Map;
struct Tile;

typedef std::shared_ptr<ActorAction> ActorActionPtr;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Map> MapPtr;
typedef std::weak_ptr<Map> MapWPtr;
typedef std::unique_ptr<Map> MapUPtr;

class Map : public std::enable_shared_from_this<Map>
{
public:
  typedef std::vector< std::vector<Tile> > TileMatrix;
  typedef std::vector<Tile> TileRow;

  Map(u32 width, u32 height, MapId id = MapId::Null);
  virtual ~Map();

  virtual MapPtr clone();

  virtual bool isExplored(int x, int y);
  virtual bool isInFov(int x, int y);
  virtual bool isBlocked(int x, int y);

  virtual void addActor(ActorPtr actor);
  virtual  bool removeActor(ActorPtr toRemove);
  virtual ActorPtr getFirstActor(int x, int y);
  virtual std::vector<ActorPtr> getActors(int x, int y, std::function<bool(ActorPtr)> filterFun = [](ActorPtr){return true;});
  virtual std::vector<ActorPtr> getActors(std::function<bool(ActorPtr)> filterFun = [](ActorPtr){return true;});
  virtual void performActionOnActors(std::function<void(ActorPtr)> func);

  virtual void render(TCODConsole* console);
  virtual void updateTile(u32 x, u32 y);
  void updateTiles();

  virtual void computeFov(int x, int y, int radius);
  virtual TCODMap& getCODMap();
  virtual void deserializeTiles(std::vector<unsigned char> tiles);
  std::vector<unsigned char> serializeTiles();

  virtual TCODColor getColor(u32 x, u32 y);
  virtual char getChar(u32 x, u32 y);
  virtual u32 getWidth() const;
  virtual void setWidth(const u32 &width);
  virtual u32 getHeight() const;
  virtual void setHeight(const u32 &height);
  virtual MapId getId() const;
  virtual void setId(const MapId &id);

  virtual void onExit(Direction direction, ActorPtr exiter);
  virtual const std::map<Direction, ActorActionPtr> getExitActions() const;

  friend class MapParser;

private:
  MapId _id;
  u32 _width, _height;
  TileMatrix _tiles;
  TCODMap _codMap;
  std::map<Direction, ActorActionPtr> _exitActions;

  Tile& getTile(u32 x, u32 y);
  void dateMapCoords(u32 x, u32 y);
  void renderTile(u32 x, u32 y, TCODConsole *console);
  void validateMapCoords(u32 x, u32 y);

};

}
#endif // MAP_H
