#ifndef CHARACTER_CLASSES
#define CHARACTER_CLASSES

#include <string>

namespace amarlon
{

enum class CharacterClassType
{
  NoClass    = 0,
  Fighter    = 1,
  Cleric     = 2,
  MagicUser  = 3,
  Thief      = 4,
  Monster    = 5
};

static inline std::string CharacterClass2Str(CharacterClassType c)
{
  std::string str = "";
  switch ( c )
  {
    case CharacterClassType::Fighter: str = "Fighter"; break;
    case CharacterClassType::Cleric: str = "Cleric"; break;
    case CharacterClassType::MagicUser: str = "Magic User"; break;
    case CharacterClassType::Thief: str = "Thief"; break;
    case CharacterClassType::Monster: str = "Monster"; break;
    default:;
  }
  return str;
}

}

#endif // CHARACTER_CLASSES

