#include "tile.h"
#include <container.h>

namespace amarlon {

Tile::Tile()
  : explored(false)
  , actors( new Container(999) )
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
    actors = std::dynamic_pointer_cast<Container>( rhs.actors->clone() );
  }
  return *this;
}

}
