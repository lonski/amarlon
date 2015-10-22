#ifndef RACES
#define RACES

#include <string>

namespace amarlon {

enum class RaceType
{
  NoRace   = 0,
  Human    = 1,
  Dwarf    = 2,
  Elf      = 3,
  Halfling = 4,
  Orc      = 5,
  Goblin   = 6,
  Undead   = 7
};

static inline std::string Race2Str(RaceType r)
{
  std::string str = "";
  switch ( r )
  {
    case RaceType::Human:    str = "Human";    break;
    case RaceType::Dwarf:    str = "Dwarf";    break;
    case RaceType::Elf:      str = "Elf";      break;
    case RaceType::Halfling: str = "Halfling"; break;
    case RaceType::Orc:      str = "Orc";      break;
    case RaceType::Goblin:   str = "Goblin";   break;
    case RaceType::Undead:   str = "Undead";   break;
    default:;
  }
  return str;
}

inline RaceType operator++(RaceType& x) { return x = (RaceType)(std::underlying_type<RaceType>::type(x) + 1); }
inline RaceType operator*(RaceType c) {return c;}
inline RaceType begin(RaceType) {return RaceType::NoRace;}
inline RaceType end(RaceType)   {return RaceType::Undead;}


}

#endif // RACES

