#ifndef CHARACTER_CLASSES
#define CHARACTER_CLASSES

#include <string>

namespace amarlon
{

enum class CharacterClass
{
  NoClass    = 0,
  Fighter    = 1,
  Cleric     = 2,
  MagicUser  = 3,
  Thief      = 4,
  Monster    = 5
};

static inline std::string CharacterClass2Str(CharacterClass c)
{
  std::string str = "";
  switch ( c )
  {
    case CharacterClass::Fighter: str = "Fighter"; break;
    case CharacterClass::Cleric: str = "Cleric"; break;
    case CharacterClass::MagicUser: str = "Magic User"; break;
    case CharacterClass::Thief: str = "Thief"; break;
    case CharacterClass::Monster: str = "Monster"; break;
  }
  return str;
}

}

#endif // CHARACTER_CLASSES

