#ifndef POINT
#define POINT

namespace amarlon {

struct Point
{
  Point(int x = 0, int y = 0)
    : x(x)
    , y(y)
  {
  }

  int x;
  int y;

  bool isNonZero() const
  {
    return x != 0 && y != 0;
  }

  bool operator==(const Point& rhs) const
  {
    return x == rhs.x && y == rhs.y;
  }

  bool operator!=(const Point& rhs) const
  {
    return !operator ==(rhs);
  }

  Point operator-(const Point& point) const
  {
    return Point( x - point.x, y - point.y );
  }

  Point operator+(const Point& point) const
  {
    return Point( x + point.x, y + point.y );
  }

};

}

#endif // POINT

