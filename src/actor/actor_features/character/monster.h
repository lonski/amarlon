#ifndef MONSTER_H
#define MONSTER_H

#include <character.h>

namespace amarlon {

class Monster : public Character
{
public:

  Monster();
  Monster(DescriptionPtr dsc);
  ~Monster();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  /* overriden functions */
  virtual CarryingCapacity::LoadLevel getLoadLevel();
  virtual int getBaseAttackBonus();
  virtual int getMeleeAttackBonus();
  virtual int getMissileAttackBonus();
  virtual Damage getDamage();
  virtual int getMorale();
  virtual bool abilityRoll(AbilityScore::Type as, int extraModifier = 0);

  virtual std::string getDescription();

private:
  int _morale;
  int _hpMod;
  Damage _damage;

  friend class MonsterSerializer;

};

typedef std::shared_ptr<Monster> MonsterPtr;

}

#endif // MONSTER_H
