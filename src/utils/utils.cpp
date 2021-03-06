#include "utils.h"
#include <actor.h>
#include <pickable.h>
#include <engine.h>
#include <map.h>
#include <world.h>
#include <direct_path.h>

namespace amarlon {

std::string getItemNameAndAmount(ActorPtr a)
{
  std::string value = a->getName();
  if ( PickablePtr pickable = a->getFeature<Pickable>() )
  {
    if ( pickable->getAmount() > 1 )
    {
      value += " (" + std::to_string(pickable->getAmount()) + ")";
    }
  }
  return value;
}

bool handleDirectionKey(const TCOD_key_t& key, int &dx, int &dy)
{
  bool handled = true;

  switch(key.vk)
  {
    case TCODK_DOWN: dy++; break;
    case TCODK_KP2: dy++; break;

    case TCODK_UP: dy--; break;
    case TCODK_KP8: dy--; break;

    case TCODK_LEFT: dx--; break;
    case TCODK_KP4: dx--; break;

    case TCODK_RIGHT: dx++; break;
    case TCODK_KP6: dx++; break;

    case TCODK_KP7: dx--; dy--; break;
    case TCODK_KP9: dx++; dy--; break;
    case TCODK_KP1: dx--; dy++; break;
    case TCODK_KP3: dx++; dy++; break;

    case TCODK_KP5:
    case TCODK_ENTER:
      //players tile
    break;

    default: handled = false; break;
  }

  return handled;
}

std::string colorToStr(TCODColor color, bool braces)
{
  std::stringstream ss;
  ss << std::setfill('0')
     << std::setw(2) << std::hex << (int)color.r
     << std::setw(2) << std::hex << (int)color.g
     << std::setw(2) << std::hex << (int)color.b;

  return braces ? "{"+ss.str()+"}" : ss.str();
}

std::string tolowers(const std::string &str)
{
  std::string r(str);
  std::transform(r.begin(), r.end(), r.begin(), ::tolower);
  return r;
}

std::vector<std::string> explode(const std::string &str, char ch)
{
  std::vector<std::string> result;
  std::string line;

  for (auto s : str)
  {
    if (s == ch)
    {
      if (!line.empty())
      {
        result.push_back(line);
        line.clear();
      }
    }
    else
    {
      line += s;
    }
  }

  if (!line.empty())
  {
    result.push_back(line);
    line.clear();
  }

  return result;
}

float calculateDistance(int ox, int oy, int tx, int ty)
{
  int dx = ox - tx;
  int dy = oy - ty;

  return sqrtf( dx*dx + dy*dy );
}

TCODPath* calculatePath(Target start, Target end)
{
  MapPtr map = Engine::instance().getWorld().getCurrentMap();
  if ( start && end && map )
  {
    TCODMap& codMap = map->getCODMap();
    TCODPath* path = new TCODPath( &codMap, 1.0f );
    path->compute( start.x, start.y, end.x, end.y );

    return path;
  }
  return nullptr;
}

float calculateDistance(amarlon::ActorPtr a1, amarlon::ActorPtr a2)
{
  if ( a1 && a2 )
  {
    int dx = a1->getX() - a2->getX();
    int dy = a1->getY() - a2->getY();

    return sqrtf( dx*dx + dy*dy );
  }
  return 0;
}

DirectPathPtr calculateDirectPath(Target start, Target end)
{
  MapPtr map = Engine::instance().getWorld().getCurrentMap();
  if ( start && end && map )
  {
    DirectPathPtr path( new DirectPath(map) );
    path->compute( Point(start.x, start.y), Point(end.x, end.y) );

    return path;
  }
  return nullptr;
}

float tangens(const Point &p1, const Point &p2)
{
  Point dp = p2 - p1;
  return dp.x != 0 ? (float)dp.y/(float)dp.x : 0.0f;
}

}

