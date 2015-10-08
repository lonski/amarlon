#include "tile_db.h"
#include <fstream>
#include <vector>
#include <utils.h>
#include <memory>
#include <tiles.pb.h>

namespace amarlon {

using namespace std;

TileDatabase::TileDatabase()
  : _tilesData( new proto::TilesData )
{
}

proto::TileData* TileDatabase::getTileData(TileType id)
{
  for( int i=0; i<_tilesData->tile_size(); ++i)
  {
    const proto::TileData& sd = _tilesData->tile(i);
    if ( sd.id() == static_cast<int>(id) ) return const_cast<proto::TileData*>(&sd);
  }
  return nullptr;
}

char TileDatabase::getChar(TileType type)
{
  proto::TileData* td = getTileData(type);
  return td != nullptr ? td->character().front() : '#';
}

TCODColor TileDatabase::getColor(TileType type)
{
  proto::TileData* td = getTileData(type);
  return td != nullptr ? strToColor(td->color()) : TCODColor::white;
}

bool TileDatabase::isWalkable(TileType type)
{
  proto::TileData* td = getTileData(type);
  return td != nullptr ? td->walkable() : false;
}

bool TileDatabase::isTransparent(TileType type)
{
  proto::TileData* td = getTileData(type);
  return td != nullptr ? td->transparent() : false;
}

bool TileDatabase::load(const string& fn)
{
  ifstream ifs(fn);

  if (ifs.is_open())
  {
    _tilesData->ParseFromIstream(&ifs);
    return true;
  }
  return false;
}

}

