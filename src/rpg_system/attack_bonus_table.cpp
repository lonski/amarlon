#include "attack_bonus_table.h"

namespace amarlon {

namespace AttackBonus
{

  int getBonus(CharacterClass charClass, int level)
  {
    return abTable[charClass][level];
  }

}}
