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
};

}

#endif // POINT

