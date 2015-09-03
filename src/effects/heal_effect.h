#ifndef HEALEFFECT_H
#define HEALEFFECT_H

#include <memory>
#include <effect.h>

namespace amarlon {

class HealEffect;
typedef std::shared_ptr<HealEffect> HealEffectPtr;

class HealEffect : public Effect
{
public:
  HealEffect();

  virtual EffectPtr clone();
  virtual bool isEqual(EffectPtr rhs);

  virtual bool apply(ActorPtr executor, const Target& target);
  virtual void load(EffectDescriptionPtr dsc);
  virtual EffectDescriptionPtr save();

  void setHealAmount(int amount);

  virtual EffectType getType() const;
  virtual int getHealAmount() const;

private:
  int _healAmount;
};

}

#endif // HEALEFFECT_H
