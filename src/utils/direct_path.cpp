#include "direct_path.h"
#include <map.h>

namespace amarlon {

DirectPath::DirectPath(MapPtr map)
  : _map(map)
{
  _current = _points.end();
}

bool DirectPath::compute(int ox, int oy, int tx, int ty)
{
  bool r = false;

  _points.clear();
  _points.push_back(Point(ox, oy));

  while ( ox != tx || oy != ty )
  {
    int dx = tx - ox;
    int dy = ty - oy;

    int stepDx = (dx > 0 ? 1:-1);
    int stepDy = (dy > 0 ? 1:-1);

    ox += dx != 0 ? stepDx : 0;
    oy += dy != 0 ? stepDy : 0;

    if ( _map->isTransparent(ox, oy) || (ox == tx && oy == ty) )
    {
      _points.push_back(Point(ox, oy));
    }
    else //failed to calculate path
    {
      r = false;
      break;
    }
  }

  _current = _points.begin();

  return r;
}

bool DirectPath::isEmpty() const
{
  return _points.empty();
}

bool DirectPath::walk(int* x, int* y)
{
  bool r = ++_current != _points.end();

  if ( r )
  {
    *x = _current->x;
    *y = _current->y;
  }
  else
  {
    _points.clear();
  }

  return r;
}

}
