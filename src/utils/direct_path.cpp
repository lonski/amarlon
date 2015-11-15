#include "direct_path.h"
#include <map.h>
#include <cmath>

namespace amarlon {

DirectPath::DirectPath(MapPtr map)
  : _map(map)
{
  _current = _points.end();
}

bool DirectPath::compute(int ox, int oy, int tx, int ty, bool force)
{
  bool r = true;

  Point point(ox, oy);
  Point endPoint(tx, ty);

  _points.clear();
  _points.push_back(point);

  float dx = tx - ox;
  float dy = ty - oy;
  float tg = dx != 0 ? dy/dx : 0;

  if ( dx != 0 && dy != 0 && std::abs(dy) > std::abs(dx) )
  {//always increment y
   //calculate x
   int last = static_cast<float>(point.y) / tg;
   while( point != endPoint)
   {
     oy < ty ? ++point.y : --point.y;
     int cx = (static_cast<float>(point.y) / tg);
     point.x += (cx - last);
     last = cx;
     _points.push_back(point);
   }
  }
  else if ( dx != 0 && dy != 0 && std::abs(dy) < std::abs(dx) )
  {//always interment x
   //calculate y
    int last = static_cast<float>(point.x) * tg;
    while( point != endPoint)
    {
      ox < tx ? ++point.x : --point.x;
      int cy = (static_cast<float>(point.x) * tg);
      point.y += (cy - last);
      last = cy;
      _points.push_back(point);
    }
  }
  else //stright line
  {
    while( point != endPoint)
    {
      if ( ox != tx ) ox < tx ? ++point.x : --point.x;
      if ( oy != ty ) oy < ty ? ++point.y : --point.y;
      _points.push_back(point);
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

Point DirectPath::walk()
{
  Point p;
  walk(&p.x, &p.y);
  return p;
}

Point DirectPath::current() const
{
  return _current != _points.end() ? *_current : Point();
}

Point DirectPath::previous() const
{
  auto prev = _current;
  std::advance(prev, -1);
  return prev != _points.end() ? *prev : Point();
}

}
