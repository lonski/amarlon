#ifndef TILEDB_H
#define TILEDB_H

#include <map>
#include <string>
#include <vector>
#include <libtcod.hpp>
#include <xml/rapidxml.hpp>
#include <tile_type.h>
#include <tile_description.h>
#include <tile_parser.h>

namespace amarlon {

class TileDB
{
public:
  TileDB();

  char getChar(TileType type);
  std::string getName(TileType type);
  TCODColor getColor(TileType type);
  bool isWalkable(TileType type);
  bool isTransparent(TileType type);

  void load(const std::string &fn);

private:
  TileParser _tileParser;
  std::map<TileType, TileDescription> _tiles;

  void parseTiles(std::vector<char>& dataToParse);

  template<typename T>
  T get(TileType type, T TileDescription::*field, T defValue);

};

}

#endif // TILEDB_H
