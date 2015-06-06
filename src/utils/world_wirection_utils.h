#ifndef WORLD_WIRECTION_UTILS
#define WORLD_WIRECTION_UTILS

#include <directions.h>

namespace amarlon {

namespace WorldDirectionUtils {

const WorldDirection WorldDirectionArray[3][3] = {
                                      {WorldDirection::NW, WorldDirection::N, WorldDirection::NE},
                                      {WorldDirection::W,  WorldDirection::Null, WorldDirection::E},
                                      {WorldDirection::SW, WorldDirection::S, WorldDirection::SE}
                                    };

const char WorldDirectionCharArray[3][3] = {
                                      {'\\','|', '/' },
                                      {'-', '*', '-'},
                                      {'/', '|', '\\'}
                                    };

inline static int getDX(WorldDirection d)
{
  int dx = 0;
  switch ( d )
  {
    case WorldDirection::N:
    case WorldDirection::S:
      dx = 0;
    break;

    case WorldDirection::SE:
    case WorldDirection::NE:
    case WorldDirection::E:
      dx = 1;
    break;

    case WorldDirection::SW:
    case WorldDirection::NW:
    case WorldDirection::W:
      dx = -1;
    break;

    default:;
  }
  return dx;
}

inline static int getDY(WorldDirection d)
{
  int dy = 0;
  switch ( d )
  {
    case WorldDirection::W:
    case WorldDirection::E:
      dy = 0;
    break;

    case WorldDirection::SE:
    case WorldDirection::S:
    case WorldDirection::SW:
      dy = 1;
    break;

    case WorldDirection::NW:
    case WorldDirection::N:
    case WorldDirection::NE:
      dy = -1;
    break;

    default:;
  }
  return dy;
}

inline static WorldDirection getDirection(int dx, int dy)
{
  return WorldDirectionArray[ 1 + dy][ 1 + dx];
}

inline static char getChar(WorldDirection d)
{
  char c = '*';
  switch ( d )
  {
    case WorldDirection::W:
    case WorldDirection::E:
      c = '-';
    break;

    case WorldDirection::SW:
    case WorldDirection::NE:
      c = '/';
    break;

    case WorldDirection::S:
    case WorldDirection::N:
      c = '|';
    break;

    case WorldDirection::NW:
    case WorldDirection::SE:
      c = '\\';
    break;

    default:;
  }

  return c;
}

}

}

#endif // WORLD_WIRECTION_UTILS

