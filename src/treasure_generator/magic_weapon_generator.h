#ifndef MAGICWEAPONGENERATOR_H
#define MAGICWEAPONGENERATOR_H

#include <vector>
#include <actor.h>

namespace amarlon {

class MagicWeaponGenerator
{
public:
  MagicWeaponGenerator();
  ActorPtr generate(const std::vector<int> baseIDs);

private:
  void rollWeaponBonuses(ActorPtr actor);
  void rollSpecialAbility(ActorPtr actor);
  void applyDamageBonus(ActorPtr actor, int roll);
  std::pair<int, int> getMeleeDamageBonus(int roll);
  std::pair<int, int> getRangedDamageBonus(int roll);
  void randomAmountForMagicAmunition(ActorPtr actor);

};

}

#endif // MAGICWEAPONGENERATOR_H
