#ifndef TILEDB_H
#define TILEDB_H

#include <map>
#include <tile_type.h>
#include <tile.pb.h>

namespace amarlon {

typedef std::shared_ptr<TileData> TileDataPtr;
class TileDB
{
public:
  TileDB();

  /**
   * @brief Returns pointer to TileData owned by DB
   */
  TileDataPtr fetch_flyweight(TileType type);

  /**
   * @brief Returns copy of TileData of given type
   */
  TileDataPtr fetch(TileType type);

  bool load(const std::string &fn);

private:
  std::map<TileType, TileDataPtr> _tiles;

};

}

#endif // TILEDB_H
