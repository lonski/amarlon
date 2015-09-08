#include "tile.h"
#include <container.h>
#include <cstring>
#include <actor.h>
#include <tile_db.h>
#include <engine.h>

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

std::vector<unsigned char> Tile::serialize()
{
  SerializedTile t;
  memset(&t, 0, sizeof(t));
  t.explored = explored;
  t.type = static_cast<int>(type);
  t.x = x;
  t.y = y;

  unsigned char* arr = reinterpret_cast<unsigned char*>(&t);
  return std::vector<unsigned char>{ arr, arr + sizeof(t) };
}

void Tile::deserialize(const SerializedTile &t)
{
  explored = t.explored;
  type = static_cast<TileType>(t.type);
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

    auto filtered = actors->content(&filterFun);

    return filtered.empty() ? nullptr : filtered.front();
  }
  return nullptr;
}

TCODColor Tile::getColor()
{
  return Engine::instance().getTileDB().getColor(type);
}

char Tile::getChar()
{
  return Engine::instance().getTileDB().getChar(type);
}

bool Tile::isWalkable() const
{
  return Engine::instance().getTileDB().isWalkable(type);
}

bool Tile::isTransparent() const
{
  return Engine::instance().getTileDB().isTransparent(type);
}

}
