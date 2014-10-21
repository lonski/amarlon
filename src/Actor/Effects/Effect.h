#ifndef EFFECT_H
#define EFFECT_H

#include <vector>
#include "EffectType.h"
#include "DataGateways/ActorDescriptions.h"
#include "Utils/SelectorType.h"

class Actor;

class Effect
{
public:
  Effect();
  virtual ~Effect() {}

  static Effect* create(EffectType type);
  static Effect* create(const EffectDescription& dsc);

  virtual bool apply(Actor* executor, std::vector<Actor*> targets) = 0;
  virtual void load(const EffectDescription& dsc) = 0;

  virtual SelectorType getSelectorType() = 0;
  virtual int getUsesCount() const;

protected:
  int _usesCount;

};

#endif // EFFECT_H