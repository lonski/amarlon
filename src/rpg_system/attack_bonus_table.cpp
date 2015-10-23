#include "attack_bonus_table.h"

namespace amarlon {

namespace AttackBonus
{

  int get(CharacterClassType charClass, int level)
  {
    return abTable[charClass][level];
  }

}}

