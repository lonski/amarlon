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

Tile::Tile()
  : _actors(new ActorContainer )
{}

Tile::Tile(const TileState& state)
  : _actors(new ActorContainer )
{
  setState(state);
}

Tile::Tile(const Tile &tile)
{
  *this = tile;
}

Tile &Tile::operator=(const Tile &rhs)
{
  if ( this != &rhs )
  {
    setState(rhs._state);
    _actors = rhs._actors->clone(); //TODO: remove when Actors moved to protobuf
  }
  return *this;
}

void Tile::setState(const TileState& state)
{
  _state = state;
  if ( !_data || _data->id() != _state.type() )
  {
    _data = Engine::instance().getTileDB()
                              .fetch_flyweight( static_cast<TileType>(_state.type()) );
  }
}

const TileState &Tile::getState() const
{
  return _state;
}

void Tile::addActor(ActorPtr actor)
{
  _actors->push_back(actor);
  _actors->sort( [](ActorPtr a1, ActorPtr a2){
    return a1->getTileRenderPriority() < a2->getTileRenderPriority();
  });
}

bool Tile::removeActor(ActorPtr actor)
{
  return _actors->remove(actor);
}

ActorContainer Tile::getActors(std::function<bool(ActorPtr)> filterFun) const
{
  return _actors->filter(filterFun);
}

ActorPtr Tile::top(std::function<bool(ActorPtr)> filterFun) const
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
  return strToColor( _data ? _data->color() : "" );
}

char Tile::getChar()
{
  return _data ? _data->character().front() : 'X';
}

bool Tile::isWalkable() const
{
  return _data ? _data->walkable() : false;
}

bool Tile::isTransparent() const
{
  return _data ? _data->transparent() : false;
}

bool Tile::isExplored() const
{
  ::google::protobuf::uint32 f = _state.flags();
  return isBitSet(f, TILE_EXPLORED_BIT);
}

void Tile::setExplored(bool explored)
{
  ::google::protobuf::uint32 f = _state.flags();

  setBit(f, TILE_EXPLORED_BIT, explored);

  _state.set_flags(f);
}

TileType Tile::getType() const
{
  return static_cast<TileType>(_state.type());
}

}

