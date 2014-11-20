#ifndef EFFECT_H
#define EFFECT_H

#include <memory>
#include <vector>
#include "EffectType.h"
#include "DataGateways/ActorDescriptions.h"

namespace amarlon {

class Actor;
class TargetSelector;
typedef std::unique_ptr<TargetSelector> TargetSelectorUPtr;

class Effect
{
public:
  Effect();
  virtual ~Effect();

  static Effect* create(EffectType type);
  static Effect* create(const EffectDescription& dsc);
  virtual Effect* clone() = 0;
  virtual bool isEqual(Effect* rhs) = 0;

  virtual bool apply(Actor* executor, std::vector<Actor*> targets) = 0;
  virtual void load(const EffectDescription& dsc) = 0;
  virtual EffectDescription save() = 0;

  virtual TargetSelector& getTargetSelector();
  virtual int getUsesCount() const;

protected:
  int _usesCount;
  TargetSelectorUPtr _targetSelector;

};

}

#endif // EFFECT_H
