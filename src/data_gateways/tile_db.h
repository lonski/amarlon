#ifndef TILEDB_H
#define TILEDB_H

#include <memory>
#include <string>
#include <vector>
#include <libtcod.hpp>
#include <tile_type.h>

namespace amarlon {

namespace proto {
  class TileData;
  class TilesData;
  typedef std::shared_ptr<TilesData> TilesDataPtr;
}

class TileDatabase
{
public:
  TileDatabase();

  char getChar(TileType type);
  TCODColor getColor(TileType type);
  bool isWalkable(TileType type);
  bool isTransparent(TileType type);

  bool load(const std::string &fn);

private:
  proto::TilesDataPtr _tilesData;
  proto::TileData* getTileData(TileType id);

};

}

#endif // TILEDB_H
