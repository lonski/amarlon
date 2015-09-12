#include "console_utils.h"
#include <utils.h>
#include <engine.h>
#include <world.h>
#include <map.h>

namespace amarlon {

void highlightCircle(int range, Target center, TCODColor color)
{
  MapPtr map = Engine::instance().getWorld().getCurrentMap();
  if ( map )
  {
    for( uint32_t y = 0; y < map->getHeight(); ++y )
    {
      for( uint32_t x = 0; x < map->getWidth(); ++x )
      {
        if ( calculateDistance(center.x, center.y, x, y ) <= range )
        {
          TCODConsole::root->setCharBackground(x,y,color);
        }
      }
    }
  }
}

void setTile(uint32_t x, uint32_t y, char c, TCODColor color)
{
  TCODConsole::root->setChar(x,y,c);
  TCODConsole::root->setCharForeground(x,y,color);
}

void renderPath(Target start, Target end)
{
  if ( start && end )
  {
    TCODPath* path = calculatePath(start, end);

    while( path && !path->isEmpty() )
    {
      int x(0), y(0);
      path->walk(&x, &y, true);
      setTile(x, y, '*', TCODColor::lighterRed);
    }

    delete path;
    setTile(end.x, end.y, 'x', TCODColor::red);
  }
}

}
