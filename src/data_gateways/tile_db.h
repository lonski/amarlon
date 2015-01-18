#ifndef TILEDB_H
#define TILEDB_H

#include <map>
#include <string>
#include <vector>
#include <libtcod.hpp>
#include "xml/rapidxml.hpp"
#include "world/tile_type.h"
#include "data_gateways/descriptions/tile_description.h"
#include "parsers/tile_parser.h"

namespace amarlon {

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

  void loadTiles(const std::string &fn);

private:
  TileParser _tileParser;
  std::map<TileType, TileDescription> _tiles;

  void parseTiles(std::vector<char>& dataToParse);

  template<typename T>
  T get(TileType type, T TileDescription::*field, T defValue);

};

}

#endif // TILEDB_H
