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

  Point& operator-=(const Point& point)
  {
    x -= point.x;
    y -= point.y;
    return *this;
  }

  Point& operator+=(const Point& point)
  {
    x += point.x;
    y += point.y;
    return *this;
  }

  Point& operator*=(int factor)
  {
    x *= factor;
    y *= factor;
    return *this;
  }

};

static inline Point operator-(Point l, Point r)
{
  l -= r;
  return l;
}

static inline Point operator+(Point l, Point r)
{
  l += r;
  return l;
}

static inline Point operator*(Point p, int f)
{
    p *= f;
    return p;
}

static inline Point operator*(int f, Point p)
{
    return p * f;
}

}

#endif // POINT

