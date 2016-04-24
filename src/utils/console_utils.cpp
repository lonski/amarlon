#include "console_utils.h"
#include <utils.h>
#include <engine.h>
#include <world.h>
#include <map.h>
#include <direct_path.h>

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

void highlightFilledCircle(int range, Target center, TCODColor color)
{  
  MapPtr map = Engine::instance().getWorld().getCurrentMap();
  TCODConsole* console = Engine::instance().getConsole();
  if ( map && console )
  {
    for( uint32_t y = 0; y < map->getHeight(); ++y )
    {
      for( uint32_t x = 0; x < map->getWidth(); ++x )
      {
        if ( calculateDistance(center.x, center.y, x, y ) <= range )
        {
          console->setCharBackground(x,y, color);
        }
      }
    }
  }
}

void setTile(uint32_t x, uint32_t y, char c, TCODColor color)
{
  TCODConsole* console = Engine::instance().getConsole();
  if ( console )
  {
    console->setChar(x,y,c);
    console->setCharForeground(x,y,color);
  }
}

void setTile(const Point &p, char c, TCODColor color)
{
  setTile(p.x, p.y, c, color);
}

void renderPath(Target start, Target end)
{
  if ( start && end )
  {
    //TCODPath* path = calculatePath(start, end);
    DirectPathPtr path = calculateDirectPath(start, end);
    while( path && !path->isEmpty() )
    {
      int x(0), y(0);
      path->walk(&x, &y);
      setTile(x, y, '*', TCODColor::lighterRed);
    }

    //delete path;
    setTile(end.x, end.y, 'x', TCODColor::red);
  }
}

void highlightCell(uint32_t x, uint32_t y)
{
  TCODConsole* console = Engine::instance().getConsole();

  if ( console )
  {
    TCODColor fgcol = console->getCharForeground(x, y);
    TCODColor bgcol = console->getCharBackground(x, y);
    console->setCharForeground(x, y, TCODColor::lerp(fgcol, TCODColor::yellow, 0.6));
    console->setCharBackground(x, y, TCODColor::lerp(bgcol, TCODColor::yellow, 0.1));
  }
}


}

