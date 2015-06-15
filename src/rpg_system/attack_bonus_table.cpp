#include "attack_bonus_table.h"

namespace amarlon {

namespace attack_bonus_table
{

  int getBonus(CharacterClass charClass, int level)
  {
    return abTable[charClass][level];
  }

}}
