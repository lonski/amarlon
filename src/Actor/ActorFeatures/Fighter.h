#ifndef FIGHTER_H
#define FIGHTER_H

#include "ActorFeature.h"
#include "DataGateways/ActorDescriptions.h"

namespace amarlon {

class Fighter : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Fighter(float power, float maxHp);
  static Fighter* create(Description* dsc);

  virtual ActorFeature::Type getType() { return featureType; }

  virtual ActorFeature* clone();
  virtual bool isEqual(ActorFeature *rhs);

  bool isAlive() const;

  void attack(Actor* enemy);
  void takeDamage(float power);
  void die();
  int heal(int hp);

  float getHp() const;
  float getMaxHp() const;

private:
  float _power;
  float _maxHp;
  float _hp;

};

}

#endif // FIGHTER_H
