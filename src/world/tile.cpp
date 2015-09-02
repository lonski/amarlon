#include "tile.h"
#include <container.h>
#include <string>
#include <sstream>
#include <map.h>

namespace amarlon {

Tile::Tile(uint32_t x, uint32_t y)
  : explored(false)
  , type(TileType::Null)
  , actors( new Container(999) )
  , x(x)
  , y(y)
{}

Tile::Tile(const Tile &tile)
{
  *this = tile;
}

Tile &Tile::operator=(const Tile &rhs)
{
  if ( this != &rhs )
  {
    explored = rhs.explored;
    type = rhs.type;
    x = rhs.x;
    y = rhs.y;
    actors = std::dynamic_pointer_cast<Container>( rhs.actors->clone() );
  }
  return *this;
}

void Tile::update(Map* map)
{
  if ( map != nullptr )
  {
    bool walkable = Map::Tiles.isWalkable(type);
    bool transparent = Map::Tiles.isTransparent(type);
    map->getCODMap().setProperties(x,y,transparent, walkable);
  }
}

std::vector<unsigned char> Tile::serialize()
{
  SerializedTile t;
  t.explored = explored;
  t.type = static_cast<int>(type);
  t.x = x;
  t.y = y;

  unsigned char* arr = reinterpret_cast<unsigned char*>(&t);
  return std::vector<unsigned char>{ arr, arr + sizeof(t) / sizeof(arr[0]) };
}

void Tile::deserialize(const SerializedTile &t)
{
  explored = t.explored;
  type = static_cast<TileType>(t.type);
  x = t.x;
  y = t.y;
}

}
