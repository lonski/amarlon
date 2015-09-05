#ifndef DAMAGE_EFFECT_H
#define DAMAGE_EFFECT_H

#include <memory>
#include <effect.h>
#include <damage_type.h>

namespace amarlon {

class DamageEffect;
typedef std::shared_ptr<DamageEffect> DamageEffectPtr;

class DamageEffect : public Effect
{
public:
  DamageEffect();

  virtual EffectPtr clone();
  virtual bool isEqual(EffectPtr rhs);

  virtual bool apply(ActorPtr executor, const Target& target);

  virtual EffectType getType() const;

  virtual void load(const Params& params);
  virtual Params toParams() const;

private:
  int _damage;
  DamageType _type;

};

}

#endif // DAMAGE_EFFECT_H
