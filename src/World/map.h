#ifndef MAP_H
#define MAP_H

#include <vector>
#include <stdexcept>
#include <libtcod.hpp>
#include "MapId.h"
#include "DataGateways/TileDB.h"
#include "DataGateways/MapGateway.h"

typedef unsigned int u32;

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

  static TileDB Tiles;
  static MapGateway Gateway;

  Map(u32 width, u32 height, MapId id = MapId::Null);

  bool isExplored(u32 x, u32 y);
  bool isInFov(u32 x, u32 y);
  bool isBlocked(u32 x, u32 y);

  bool render(TCODConsole* console);

  void computeFov(u32 x, u32 y, int radius);
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
  u32 _width, _height;
  TileMatrix _tiles;
  TCODMap codMap;
  MapId _id;

  Tile& getTile(u32 x, u32 y);
  void validateMapCoords(u32 x, u32 y);

};

#endif // MAP_H
