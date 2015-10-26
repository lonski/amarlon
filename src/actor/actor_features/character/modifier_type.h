#ifndef MODIFIER_TYPE
#define MODIFIER_TYPE

#include <cstring>
#include <saving_throws_table.h>
#include <damage_type.h>
#include <skill_id.h>
#include <utils.h>

namespace amarlon {

enum class GenericModifier
{
  AttackBonus            = 0,
  MoraleModifier         = 1,
  MissileAttackBonus     = 2,
  ExperiencePercentBonus = 3
};

struct ModifierType
{
  ModifierType()
  {
    memset(this, -1, sizeof(ModifierType));
  }

  ModifierType(const std::string& s)
  {
    fromString(s);
  }

  std::string toString() const
  {
    std::string str;
    str += std::to_string( (int)generic ) + "#";
    str += std::to_string( (int)savingThrow ) + "#";
    str += std::to_string( (int)dmg ) + "#";
    str += std::to_string( (int)ac ) + "#";
    str += std::to_string( (int)skill ) + "#";
    return str;
  }

  void fromString(const std::string& str)
  {
    memset(this, -1, sizeof(ModifierType));

    std::vector<std::string> vals = explode(str, '#');
    if ( vals.size() > 0 ) generic     = static_cast<GenericModifier>   ( fromStr<int>(vals[0]) );
    if ( vals.size() > 1 ) savingThrow = static_cast<SavingThrows::Type>( fromStr<int>(vals[1]) );
    if ( vals.size() > 2 ) dmg         = static_cast<DamageType>        ( fromStr<int>(vals[2]) );
    if ( vals.size() > 3 ) ac          = static_cast<DamageType>        ( fromStr<int>(vals[3]) );
    if ( vals.size() > 4 ) skill       = static_cast<SkillId>           ( fromStr<int>(vals[4]) );
  }

  bool operator==(const ModifierType& rhs )
  {
    return savingThrow == rhs.savingThrow &&
           dmg == rhs.dmg &&
           ac == rhs.ac &&
           generic == rhs.generic &&
           skill == rhs.skill;
  }

  GenericModifier generic;
  SavingThrows::Type savingThrow;
  DamageType dmg;
  DamageType ac;
  SkillId skill;

};


}

#endif // MODIFIER_TYPE

