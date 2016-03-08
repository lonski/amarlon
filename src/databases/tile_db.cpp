#include "tile_db.h"
#include <fstream>
#include <memory>

namespace amarlon {

using namespace std;

TileDB::TileDB()
{
}

TileDataPtr TileDB::fetch_flyweight(TileType type)
{
  auto it = _tiles.find(type);
  if ( it != _tiles.end() ) return it->second;

  return nullptr;
}

TileDataPtr TileDB::fetch(TileType type)
{
  if ( TileDataPtr tile = fetch_flyweight(type) )
  {
    TileDataPtr copied_tile( new TileData );
    copied_tile->CopyFrom(*tile);
    return copied_tile;
  }

  return nullptr;
}

bool TileDB::load(const string& fn)
{
  std::ifstream ifs(fn);
  if ( ifs.is_open() )
  {
    _tiles.clear();

    TilesData tiles;
    tiles.ParseFromIstream(&ifs);

    for ( auto it = tiles.tile().begin(); it != tiles.tile().end(); ++it )
    {
      TileDataPtr tile( new TileData );
      tile->CopyFrom(*it);
      _tiles[ static_cast<TileType>(it->id()) ] = tile;
    }

    printf("Parsed tiles %d", _tiles.size());
    return true;
  }
  return false;
}

}

