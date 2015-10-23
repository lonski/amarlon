#ifndef MODIFIER_TYPE
#define MODIFIER_TYPE

#include <cstring>
#include <saving_throws_table.h>
#include <damage_type.h>

namespace amarlon {

enum class GenericModifier
{
  AttackBonus    = 0,
  MoraleModifier = 1
};

struct ModifierType
{
  ModifierType()
  {
    memset(this, -1, sizeof(ModifierType));
  }

  bool operator==(const ModifierType& rhs )
  {
    return savingThrow == rhs.savingThrow &&
           dmg == rhs.dmg &&
           ac == rhs.ac &&
           generic == rhs.generic;
  }

  GenericModifier generic;
  SavingThrows::Type savingThrow;
  DamageType dmg;
  DamageType ac;

};


}

#endif // MODIFIER_TYPE

