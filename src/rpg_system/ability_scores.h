#ifndef ABILITY_SCORES
#define ABILITY_SCORES

#include <map>

namespace amarlon {

namespace AbilityScore
{
  enum Type
  {
    STR,
    INT,
    WIS,
    DEX,
    CON,
    CHA
  };
  const int MIN_VALUE = 3;
  const int MAX_VALUE = 18;

  static std::map<int, int> modifiersMap = {
  /* Value, Modifier */
    {3,     -3},
    {4,     -2},
    {5,     -2},
    {6,     -1},
    {7,     -1},
    {8,     -1},
    {9,      0},
    {10,     0},
    {11,     0},
    {12,     0},
    {13,     1},
    {14,     1},
    {15,     1},
    {16,     2},
    {17,     2},
    {18,     3}
  };

  int getModifier( int abilityScoreValue );

}

}

#endif // ABILITY_SCORES

