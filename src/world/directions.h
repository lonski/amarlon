#ifndef DIRECTIONS
#define DIRECTIONS

namespace amarlon {

enum class Direction
{
  Null  = 0,
  West  = 1,
  East  = 2,
  North = 3,
  South = 4,
  Up    = 5,
  Down  = 6
};

enum class WorldDirection
{
  Null = 0,
  N  = 1,
  NE = 2,
  E  = 3,
  SE = 4,
  S  = 5,
  SW = 6,
  W  = 7,
  NW = 8
};

inline WorldDirection operator++(WorldDirection& x)
{
  return x == WorldDirection::NW ? x = WorldDirection::N : x = (WorldDirection)(std::underlying_type<WorldDirection>::type(x) + 1);
}
inline WorldDirection operator--(WorldDirection& x)
{
  return x == WorldDirection::N ? x = WorldDirection::NW : x = (WorldDirection)(std::underlying_type<WorldDirection>::type(x) - 1);
}

}

#endif // DIRECTIONS

