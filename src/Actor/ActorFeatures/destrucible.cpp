#include "destrucible.h"

Destrucible::Destrucible(float maxHp)
  : _maxHp(maxHp)
  , _hp(maxHp)
{
}

bool Destrucible::isAlive() const
{
  return (_hp > 0);
}
