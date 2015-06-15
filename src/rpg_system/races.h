#ifndef RACES
#define RACES

#include <string>

namespace amarlon {

enum class Race
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

static inline std::string Race2Str(Race r)
{
  std::string str = "";
  switch ( r )
  {
    case Race::Human:    str = "Human";    break;
    case Race::Dwarf:    str = "Dwarf";    break;
    case Race::Elf:      str = "Elf";      break;
    case Race::Halfling: str = "Halfling"; break;
    case Race::Orc:      str = "Orc";      break;
    case Race::Goblin:   str = "Goblin";   break;
    case Race::Undead:   str = "Undead";   break;
    default:;
  }
  return str;
}

}

#endif // RACES

