#ifndef HEALEFFECT_H
#define HEALEFFECT_H

#include "Effect.h"

class HealEffect : public Effect
{
public:
  HealEffect();

  virtual bool apply(Actor* executor, std::vector<Actor*> targets);
  virtual void load(const EffectDescription& dsc);

  virtual SelectorType getSelectorType()
  {
    return SelectorType::Executor;
  }

private:
  int _healAmount;

};

#endif // HEALEFFECT_H
