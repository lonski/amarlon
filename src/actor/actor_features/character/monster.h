#ifndef MONSTER_H
#define MONSTER_H

#include <character.h>

namespace amarlon {

class Monster : public Character
{
public:

  class Creator : public Character::Creator
  {
  public:
    virtual ~Creator() {}
    virtual CharacterPtr create(CharacterDescriptionPtr dsc);
  };

  Monster(int level, int hitPointsBonus = 0);
  ~Monster();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  /* overriden functions */
  virtual CarryingCapacity::LoadLevel getLoadLevel();
  virtual int getBaseAttackBonus();
  virtual int getMeleeAttackBonus();
  virtual Damage getDamage();

  virtual std::string getDescription();

  /* class specific functions */
  virtual int getMorale();

private:
  int _morale;
  int _hpMod;
  Damage _damage;

  friend class Monster::Creator;
  friend class MonsterSerializer;

};

typedef std::shared_ptr<Monster> MonsterPtr;

}

#endif // MONSTER_H
