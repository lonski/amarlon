#include "console_utils.h"
#include <utils.h>
#include <engine.h>
#include <world.h>
#include <map.h>

namespace amarlon {

void drawCircle(int radius, Target center, char c, TCODColor color)
{
  MapPtr map = Engine::instance().getWorld().getCurrentMap();
  if ( map )
  {
    for( uint32_t y = 0; y < map->getHeight(); ++y )
    {
      for( uint32_t x = 0; x < map->getWidth(); ++x )
      {
        float distance = calculateDistance(center.x, center.y, x, y );
        if ( distance < radius && distance >= radius - 1 )
        {
          if ( !map->isBlocked(x,y) && map->isInFov(x,y) )
          {
            setTile(x,y,c,color);
          }
        }
      }
    }
  }
}

void highlightFilledCircle(int range, Target center)
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
          TCODConsole::root->setCharBackground(x,y, TCODColor::lighterYellow * 0.1);
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

void highlightCell(uint32_t x, uint32_t y)
{
  TCODColor fgcol = TCODConsole::root->getCharForeground(x, y);
  TCODColor bgcol = TCODConsole::root->getCharBackground(x, y);
  TCODConsole::root->setCharForeground(x, y, TCODColor::lerp(fgcol, TCODColor::yellow, 0.6));
  TCODConsole::root->setCharBackground(x, y, TCODColor::lerp(bgcol, TCODColor::yellow, 0.1));
}

}

