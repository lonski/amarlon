#ifndef MAP_H
#define MAP_H

#include <vector>
#include <list>
#include <stdexcept>
#include <libtcod.hpp>
#include "MapId.h"
#include "DataGateways/TileDB.h"
#include "DataGateways/MapGateway.h"

typedef unsigned int u32;

class Actor;

struct Tile
{
  bool explored;
  TileType type;

  Tile()
    : explored(false)
  {}
};

class Map
{
public:
  typedef std::vector< std::vector<Tile> > TileMatrix;
  typedef std::vector<Tile> TileRow;
  typedef std::list<Actor*> ActorArray;

  static TileDB Tiles;
  static MapGateway Gateway;

  Map(u32 width, u32 height, MapId id = MapId::Null);

  bool isExplored(int x, int y);
  bool isInFov(int x, int y);
  bool isBlocked(int x, int y);

  void addActor(Actor* actor);
  Actor* getFirstActor(int x, int y);
  std::vector<Actor*> getActors(int x, int y, bool (*filterFun)(Actor *) = nullptr);
  std::vector<Actor*> getActors(bool (*filterFun)(Actor *));
  bool removeActor(Actor *toRemove);
  const ActorArray& actors() const;

  void render(TCODConsole* console);
  void updateActorCells();
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
  ActorArray _actors;

  Tile& getTile(u32 x, u32 y);
  void validateMapCoords(u32 x, u32 y);

};

#endif // MAP_H
