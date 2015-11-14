#ifndef DIRECT_PATH_H
#define DIRECT_PATH_H

#include <memory>
#include <list>

namespace amarlon {

class Map;
typedef std::shared_ptr<Map> MapPtr;

struct Point
{
  Point(int x = 0, int y = 0)
    : x(x)
    , y(y)
  {
  }

  int x;
  int y;
};

class DirectPath
{
public:
  DirectPath(MapPtr map);

  bool compute(int ox, int oy, int tx, int ty);
  bool isEmpty() const;
  bool walk(int* x, int* y);

private:
  MapPtr _map;
  std::list<Point> _points;
  std::list<Point>::iterator _current;

};

}

#endif // DIRECT_PATH_H
