#include "attack_bonus_table.h"

namespace amarlon {

namespace AttackBonusTable
{

  int getBonus(CharacterClass charClass, int level)
  {
    std::map<int, int>& source = AttackBonusTable::fighterAB;
    switch ( charClass )
    {
      case CharacterClass::FIGHTER:
        source = AttackBonusTable::fighterAB;
      break;

      case CharacterClass::CLERIC:
      case CharacterClass::THIEF:
        source = AttackBonusTable::clericOrThiefAB;
      break;

      case CharacterClass::MAGIC_USER:
        source = AttackBonusTable::magicUserAB;
      break;

      case CharacterClass::MONSTER:
        source = AttackBonusTable::monsterAB;
      break;

      default:;
    }

    auto abIter = source.find(level);

    return abIter == source.end() ? source.rbegin()->second : abIter->second;
  }

}}
