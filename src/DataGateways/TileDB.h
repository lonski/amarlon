#ifndef TILEDB_H
#define TILEDB_H

#include <map>
#include "libtcod.hpp"
#include "xml/rapidxml.hpp"
#include "World/TileType.h"

struct TileDescription
{
  char character;
  char code;
  TCODColor color;
  bool walkable;
  bool transparent;
};

class TileDB
{
public:
  TileDB();

  TileType getType(char ch);
  char getChar(TileType type);
  char getCode(TileType type);
  TCODColor getColor(TileType type);
  bool isWalkable(TileType type);
  bool isTransparent(TileType type);

  bool loadTiles(std::string fn);

private:
  std::map<TileType, TileDescription> _tiles;

};

#endif // TILEDB_H
