#ifndef MAP_H
#define MAP_H

#include <vector>
#include <functional>
#include <memory>
#include <list>
#include <stdexcept>
#include <libtcod.hpp>
#include <world/map_id.h>
#include "DataGateways/TileDB.h"
#include "DataGateways/MapGateway.h"
#include <Actor/ActorFeatures/Container.h>

namespace amarlon {

typedef unsigned int u32;

class Actor;

typedef std::shared_ptr<Container> ContainerPtr;

struct Tile
{
  bool explored;
  TileType type;
  ContainerPtr actors;

  Tile()
    : explored(false)
    , actors( new Container(999) )
  {}
};

class Map
{
public:
  typedef std::vector< std::vector<Tile> > TileMatrix;
  typedef std::vector<Tile> TileRow;

  static TileDB Tiles;
  static MapGateway Gateway;

  Map(u32 width, u32 height, MapId id = MapId::Null);
  ~Map();

  bool isExplored(int x, int y);
  bool isInFov(int x, int y);
  bool isBlocked(int x, int y);

  void addActor(Actor* actor);
  bool removeActor(Actor *toRemove);
  Actor* getFirstActor(int x, int y);
  std::vector<Actor*> getActors(int x, int y, bool (*filterFun)(Actor *) = nullptr);
  std::vector<Actor*> getActors(std::function<bool(Actor*)>* filterFun);
  Container& getActorsContainer(u32 x, u32 y);

  void performActionOnActors(std::function<void(Actor*)> func);

  void render(TCODConsole* console);
  void updateActorCell(Actor *actor);

  void computeFov(int x, int y, int radius);
  void fill(std::string tilesStr);
  std::string tilesToStr();

  //setters and getters
  TCODColor getColor(u32 x, u32 y);
  char getChar(u32 x, u32 y);
  u32 getWidth() const;
  void setWidth(const u32 &width);
  u32 getHeight() const;
  void setHeight(const u32 &height);
  MapId getId() const;
  void setId(const MapId &id);

private:
  MapId _id;
  u32 _width, _height;
  TileMatrix _tiles;
  TCODMap codMap;

  Tile& getTile(u32 x, u32 y);
  void validateMapCoords(u32 x, u32 y);
  void renderTile(u32 x, u32 y, TCODConsole *console);
  void renderActorsOnTile(u32 x, u32 y, TCODConsole *console);

};

}
#endif // MAP_H