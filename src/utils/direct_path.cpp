#include "direct_path.h"
#include <map.h>
#include <cmath>
#include <utils.h>

namespace amarlon {

DirectPath::DirectPath(MapPtr map)
  : _map(map)
  , _tg(0.0f)
{
  _position = _points.end();
}

bool DirectPath::compute(const Point& start, const Point& end, bool force)
{
  bool r = true;
  Point current = start;

  _tg = tangens(current, end);
  _points.clear();
  _points.push_back(current);

  while( current != end )
  {
    current = calculateNextPoint(current, end);

    if ( _map->isTransparent(current) ||
         current == end ||
         force )
    {
      _points.push_back( current );
    }
    else
    {
      r = false;
      _points.clear();
      break;
    }
  }

  _position = _points.begin();

  return r;
}

void DirectPath::extrapolate(int count)
{
  if ( _points.size() > 1 )
  {
    auto iter = _points.end();
    std::advance(iter, -1);
    Point point = *iter;

    Point start = *_points.begin();
    Point dp = start - point;
    float distance = sqrtf( dp.x*dp.x + dp.y*dp.y );
    if ( distance < count ) dp = dp * std::max( count - distance, 1.0f);
    Point mirroredEnd( point.x - dp.x, point.y - dp.y);

    while ( count-- && point != mirroredEnd )
    {
      point = calculateNextPoint(point, mirroredEnd);
      _points.push_back(point);
    }
  }
}

Point DirectPath::calculateNextPoint(const Point& previous, const Point& end)
{
  Point dp = end - previous;
  Point next = previous;

  if ( dp.isNonZero() && std::abs(dp.y) > std::abs(dp.x) )
  {
    if( dp.y != 0) dp.y > 0 ? ++next.y : --next.y;
    next.x += ((int)(next.y / _tg) - (int)(previous.y / _tg));
  }
  else if ( dp.isNonZero()  && std::abs(dp.y) < std::abs(dp.x) )
  {
    if( dp.x != 0) dp.x > 0 ? ++next.x : --next.x;
    next.y += ((int)(next.x * _tg) - (int)(previous.x * _tg));
  }
  else
  {
    if( dp.x != 0) dp.x > 0 ? ++next.x : --next.x;
    if( dp.y != 0) dp.y > 0 ? ++next.y : --next.y;
  }

  return next;
}

bool DirectPath::isEmpty() const
{
  return _points.empty();
}

bool DirectPath::walk(int* x, int* y)
{
  bool r = ++_position != _points.end();

  if ( r )
  {
    *x = _position->x;
    *y = _position->y;
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
  return _position != _points.end() ? *_position : Point();
}

Point DirectPath::previous() const
{
  auto prev = _position;
  std::advance(prev, -1);
  return prev != _points.end() ? *prev : Point();
}

}
