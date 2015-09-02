#ifndef HEALEFFECT_H
#define HEALEFFECT_H

#include "effect.h"

namespace amarlon {

class SelfHealEffect : public Effect
{
public:
  SelfHealEffect();

  virtual Effect* clone();
  virtual bool isEqual(Effect *rhs);

  virtual bool apply(ActorPtr executor, const Target& target);
  virtual void load(const EffectDescription& dsc);
  virtual EffectDescription save();

  void setHealAmount(int amount);

  virtual EffectType getType() const;
  virtual int getHealAmount() const;

private:
  int _healAmount;
};

}

#endif // HEALEFFECT_H
