#include "damage.h"


namespace amarlon {

Damage::Damage(int value_, int diceCount_, dices::Dice dice_, DamageType type_)
  : value(value_)
  , diceCount(diceCount_)
  , dice(dice_)
  , type(type_)
{
}

Damage::Damage(const std::string &dmgInStr)
{
  parse(dmgInStr);
}

int Damage::roll() const
{
  return std::max( dices::roll(dice, diceCount) + value, 1); //always minimum 1 dmg inflicted
}

bool Damage::operator==(const Damage &rhs) const
{
  return value == rhs.value &&
         diceCount == rhs.diceCount &&
         dice  == rhs.dice &&
         type  == rhs.type;
}

bool Damage::operator!=(const Damage &rhs) const
{
  return !(*this == rhs);
}

bool Damage::operator>(const Damage &rhs) const
{
  return toInt() > rhs.toInt();
}

bool Damage::operator<(const Damage &rhs) const
{
  return toInt() < rhs.toInt();
}

Damage::operator std::string() const
{
  return toStr();
}

std::string Damage::toStr() const
{
  // Example format: "1d4+5#0"
  return std::to_string(diceCount) +              // 1
         "d" +                                    // d
         std::to_string(static_cast<int>(dice)) + // 4
         "+" +                                    // +
         std::to_string(value) +                  // 5
         "#" +                                    // #
      std::to_string(static_cast<int>(type));     // 0
}

int Damage::toInt() const
{
  return static_cast<int>(dice) * diceCount + value;
}

void Damage::parse(const std::string &str)
{
  // Example format: "1d4+5#0"
  const short MINIMUM_LENGTH = 7;

  value = 0;
  diceCount = 0;
  dice = dices::NoDice;
  type = DamageType::Physical;

  if ( str.size() >= MINIMUM_LENGTH )
  {
    // Extract damage type: "1d4+5" "0"
    auto dType = explode(str, '#');
    if ( dType.size() == 2 )
    {
      type = static_cast<DamageType>(fromStr<int>(dType[1]));

      // Extract damage bonus: "1d4" "5"
      auto dBonus = explode(dType[0], '+');
      if ( dBonus.size() == 2 )
      {
        value = fromStr<int>(dBonus[1]);

        // Extract dice: "1" "4"
        auto dDice = explode(dBonus[0], 'd');
        if ( dDice.size() == 2 )
        {
          diceCount = fromStr<int>(dDice[0]);
          dice = static_cast<dices::Dice>( fromStr<int>(dDice[1]) );
        }
      }
    }
  }
}

}

