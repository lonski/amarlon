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

  inline Type operator++(Type& x) { return x = (Type)(std::underlying_type<Type>::type(x) + 1); }
  inline Type operator*(Type c) {return c;}
  inline Type begin(Type) {return Type::STR;}
  inline Type end(Type)   {return Type::CHA;}

  static std::map< Type, std::string > asString
  {
    { STR, "STR" },
    { INT, "INT" },
    { WIS, "WIS" },
    { DEX, "DEX" },
    { CON, "CON" },
    { CHA, "CHA" }
  };

  static inline std::string toStr(Type as)
  {
    return asString[as];
  }

}

}

#endif // ABILITY_SCORES

