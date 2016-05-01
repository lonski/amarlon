#include "tile.h"
#include <actor_container.h>
#include <cstring>
#include <actor.h>
#include <tile_db.h>
#include <engine.h>
#include <utils.h>

namespace amarlon {

/* Flag bits */
const int TILE_EXPLORED_BIT = 1;
const int TILE_DARK_BIT     = 2;

Tile::Tile()
  : _actors(new ActorContainer )
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
    _flags = rhs._flags;
    _actors = rhs._actors->clone();
  }
  return *this;
}

void Tile::addActor(ActorPtr actor)
{
  _actors->push_back(actor);
  _actors->sort( [](ActorPtr a1, ActorPtr a2){ return a1->getTileRenderPriority() < a2->getTileRenderPriority();} );
}

bool Tile::removeActor(ActorPtr actor)
{
  return _actors->remove(actor);
}

ActorContainer Tile::getActors(std::function<bool(ActorPtr)> filterFun)
{
  return _actors->filter(filterFun);
}

bool Tile::isDark() const
{
  return isBitSet(_flags, TILE_DARK_BIT);
}

std::vector<unsigned char> Tile::serialize()
{
  SerializedTile t;
  memset(&t, 0, sizeof(t));

  t.flags = _flags;
  t.type = static_cast<uint8_t>(_type);

  unsigned char* arr = reinterpret_cast<unsigned char*>(&t);
  return std::vector<unsigned char>{ arr, arr + sizeof(t) };
}

void Tile::deserialize(const SerializedTile &t)
{
  _flags = t.flags;
  _type = static_cast<TileType>(t.type);
}

ActorPtr Tile::top(std::function<bool(ActorPtr)> filterFun)
{
  if ( !_actors->empty() )
  {
    auto filtered = _actors->filter(filterFun);
    return filtered.empty() ? nullptr : filtered.front();
  }
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

