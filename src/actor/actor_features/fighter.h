#ifndef FIGHTER_H
#define FIGHTER_H

#include "actor_feature.h"
#include "data_gateways/actor_descriptions.h"

namespace amarlon {

class Fighter;
typedef std::shared_ptr<Fighter> FighterPtr;

class Fighter : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Fighter(float power, float maxHp);
  static FighterPtr create(DescriptionPtr dsc);

  virtual ActorFeature::Type getType() { return featureType; }

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs);

  bool isAlive() const;

  void attack(ActorPtr enemy);
  void takeDamage(float power);
  void die();
  int heal(int hp);

  float getHp() const;
  void setHp(float);

  float getMaxHp() const;
  void setMaxHp(float);

  float getPower() const;
  void setPower(float);

private:
  float _power;
  float _maxHp;
  float _hp;

};


}

#endif // FIGHTER_H
