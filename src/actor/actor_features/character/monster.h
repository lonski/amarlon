#ifndef MONSTER_H
#define MONSTER_H

#include <character.h>

namespace amarlon {

class Monster : public Character
{
public:
  Monster(int level, int hitPointsBonus = 0);
  ~Monster();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs);

  /* overriden functions */
  virtual CarryingCapacity::LoadLevel getLoadLevel();
  virtual int getBaseAttackBonus();
  virtual int getMeleeAttackBonus();
  virtual int rollMeleeDamage();

  virtual std::string getDescription();

  /* class specific functions */
  virtual int getMorale();

private:
  dices::Dice _damageDice;  
  int _damageDiceCount;
  int _morale;
  int _hpMod;

  friend class Character;

};

typedef std::shared_ptr<Monster> MonsterPtr;

}

#endif // MONSTER_H
