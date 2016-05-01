#ifndef MAP_H
#define MAP_H

#include <vector>
#include <functional>
#include <memory>
#include <map>
#include <stdexcept>
#include <libtcod.hpp>
#include <directions.h>
#include <point.h>

namespace amarlon {

typedef unsigned int u32;

class Actor;
class ActorAction;
class Map;
struct Tile;
struct MapDescription;

typedef std::shared_ptr<MapDescription> MapDescriptionPtr;
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

  Map(u32 width = 100, u32 height = 60, int id = 0);
  void deserializeTiles(std::vector<unsigned char> tiles);
  std::string serializeTiles();
  void deserialize(MapDescriptionPtr dsc);
  MapDescriptionPtr toDescriptionStruct();
  ~Map();

  MapPtr clone();

  bool isExplored(int x, int y);
  bool isExplored(const Point& p);
  bool isInFov(int x, int y);
  bool isInFov(const Point& p);
  bool isBlocked(int x, int y);
  bool isBlocked(const Point& p);
  bool isTransparent(int x, int y) const;
  bool isTransparent(const Point& p) const;
  bool isDark(int x, int y) const;
  bool isDark(const Point& p) const;

  void addActor(ActorPtr actor);
  bool removeActor(ActorPtr toRemove);
  ActorPtr getFirstActor(int x, int y);
  std::vector<ActorPtr> getActors(int x, int y, std::function<bool(ActorPtr)> filterFun = [](ActorPtr){return true;});
  std::vector<ActorPtr> getActors(const Point& p, std::function<bool(ActorPtr)> filterFun = [](ActorPtr){return true;});
  std::vector<ActorPtr> getActors(int x, int y, int radius, std::function<bool(ActorPtr)> filterFun);
  std::vector<ActorPtr> getActors(int x, int y, int radius);
  std::vector<ActorPtr> getActors(std::function<bool(ActorPtr)> filterFun);
  std::vector<ActorPtr> getActors();
  void performActionOnActors(std::function<void(ActorPtr)> func);

  void render(TCODConsole* console);
  void updateTile(u32 x, u32 y);
  void updateTiles();

  void computeFov(int x, int y, int radius);
  TCODMap& getCODMap();

  TCODColor getColor(u32 x, u32 y);
  char getChar(u32 x, u32 y);
  u32 getWidth() const;
  void setWidth(const u32 &width);
  u32 getHeight() const;
  void setHeight(const u32 &height);
  int getId() const;
  void setId(const int &id);
  std::string getName() const;

  void onExit(Direction direction, ActorPtr exiter);
  const std::map<Direction, ActorActionPtr> getExitActions() const;

  friend class MapParser;

private:
  int _id;
  u32 _width, _height;
  std::string _name;
  TileMatrix _tiles;
  std::shared_ptr<TCODMap> _codMap;
  std::map<Direction, ActorActionPtr> _exitActions;

  Tile& getTile(u32 x, u32 y);
  const Tile& getTile(u32 x, u32 y) const;
  void dateMapCoords(u32 x, u32 y);
  void renderTile(u32 x, u32 y, TCODConsole *console);
  void validateMapCoords(u32 x, u32 y) const;
  void allocateTiles();

};

}
#endif // MAP_H
