#ifndef DIRECT_PATH_H
#define DIRECT_PATH_H

#include <memory>
#include <list>
#include <point.h>

namespace amarlon {

class Map;
typedef std::shared_ptr<Map> MapPtr;



class DirectPath
{
public:
  DirectPath(MapPtr map);

  /**
   * @brief Calculatec the points to move from (ox,oy) to (tx, ty)
   * @param force - if true calculates the path no mater if its blocked or not.
   *        If false, the computation end when non transparent tile is on the way.
   * @return
   */
  bool compute(const Point& start, const Point& end, bool force = false);

  bool isEmpty() const;
  bool walk(int* x, int* y);
  Point walk();
  Point current() const;
  Point previous() const;

private:
  MapPtr _map;
  std::list<Point> _points;
  std::list<Point>::iterator _position;

  float _tg;

  Point calculateNextPoint(const Point &previous, const Point &end);

};

}

#endif // DIRECT_PATH_H
