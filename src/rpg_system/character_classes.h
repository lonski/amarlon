#ifndef CHARACTER_CLASSES
#define CHARACTER_CLASSES

#include <string>

namespace amarlon
{

enum class CharacterClass
{
  FIGHTER = 0,
  CLERIC = 1,
  MAGIC_USER = 2,
  THIEF = 3,
  MONSTER = 4
};

static inline std::string CharacterClass2Str(CharacterClass c)
{
  std::string str = "";
  switch ( c )
  {
    case CharacterClass::FIGHTER: str = "Fighter"; break;
    case CharacterClass::CLERIC: str = "Cleric"; break;
    case CharacterClass::MAGIC_USER: str = "Magic User"; break;
    case CharacterClass::THIEF: str = "Thief"; break;
    case CharacterClass::MONSTER: str = "Monster"; break;
  }
  return str;
}

}

#endif // CHARACTER_CLASSES

