#ifndef DAMAGE
#define DAMAGE

#include <damage_type.h>
#include <dices.h>
#include <string>
#include <utils.h>
#include <map>
#include <species_type.h>

namespace amarlon {

struct Damage
{
  Damage(int value_ = 0,
         int diceCount_ = 0,
         dices::Dice dice_ = dices::NoDice,
         DamageType type_ = DamageType::Physical);

  Damage(const std::string& dmgInStr);

  int value;
  int diceCount;
  dices::Dice dice;
  DamageType type;
  std::map<SpeciesType, int> specialDamage;

  int roll(SpeciesType vs = SpeciesType::Null) const;

  bool operator==(const Damage& rhs) const;
  bool operator!=(const Damage& rhs) const;
  bool operator>(const Damage& rhs) const;
  bool operator<(const Damage& rhs) const;
  Damage& operator+=(const Damage& rhs);
  Damage& operator-=(const Damage& rhs);
  operator std::string() const;
  std::string toStr(bool displaySafe = false) const;
  int toInt() const;

private:
  void parse(const std::string& str);

};

}

#endif // DAMAGE

