#include "tile.h"
#include <actor_container.h>
#include <cstring>
#include <actor.h>
#include <tile_db.h>
#include <engine.h>
#include <utils.h>

namespace amarlon {

const int TILE_EXPLORED_BIT = 1;

Tile::Tile(uint32_t x, uint32_t y)
  : actors(new ActorContainer )
  , x(x)
  , y(y)
  , _flags(0)
  , _type(TileType::Null)
{}

Tile::Tile(const Tile &tile)
{
  *this = tile;
}

Tile &Tile::operator=(const Tile &rhs)
{
  if ( this != &rhs )
  {
    _type = rhs._type;
    x = rhs.x;
    y = rhs.y;
    _flags = rhs._flags;
    actors = rhs.actors->clone();
  }
  return *this;
}

std::vector<unsigned char> Tile::serialize()
{
  SerializedTile t;
  memset(&t, 0, sizeof(t));

  t.flags = _flags;
  t.type = static_cast<uint8_t>(_type);
  t.x = x;
  t.y = y;

  unsigned char* arr = reinterpret_cast<unsigned char*>(&t);
  return std::vector<unsigned char>{ arr, arr + sizeof(t) };
}

void Tile::deserialize(const SerializedTile &t)
{
  _flags = t.flags;
  _type = static_cast<TileType>(t.type);
  x = t.x;
  y = t.y;
}

ActorPtr Tile::top(std::function<bool(ActorPtr)> filterFun)
{
  if ( !actors->empty() )
  {
    //todo: move to add() function after its implementation or something else to not sort every time
    actors->sort([](ActorPtr a1, ActorPtr a2)
                    {
                      return a1->getTileRenderPriority() > a2->getTileRenderPriority();
                    });

    auto filtered = actors->filter(filterFun);

    return filtered.empty() ? nullptr : filtered.front(); }
  return nullptr;
}

TCODColor Tile::getColor()
{
  return Engine::instance().getTileDB().getColor(_type);
}

char Tile::getChar()
{
  return Engine::instance().getTileDB().getChar(_type);
}

bool Tile::isWalkable() const
{
  return Engine::instance().getTileDB().isWalkable(_type);
}

bool Tile::isTransparent() const
{
  return Engine::instance().getTileDB().isTransparent(_type);
}

bool Tile::isExplored() const
{
  return isBitSet(_flags, TILE_EXPLORED_BIT);
}

void Tile::setExplored(bool explored)
{
  setBit(_flags, TILE_EXPLORED_BIT, explored);
}

TileType Tile::getType() const
{
  return _type;
}

}
