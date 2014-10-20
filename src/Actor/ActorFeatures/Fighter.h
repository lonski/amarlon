#ifndef FIGHTER_H
#define FIGHTER_H

#include "ActorFeature.h"
#include "DataGateways/ActorDescriptions.h"

class Fighter : public ActorFeature
{
public:
  Fighter(float power, float maxHp);
  static Fighter* create(const FighterDescription& dsc);

  bool isAlive() const;

  void attack(Actor* enemy);
  void takeDamage(float power);
  void die();
  int heal(int hp);

private:
  float _power;
  float _maxHp;
  float _hp;

};

#endif // FIGHTER_H
