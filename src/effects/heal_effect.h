#ifndef HEALEFFECT_H
#define HEALEFFECT_H

#include <memory>
#include <effect.h>
#include <damage.h>

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
  virtual bool revoke(ActorPtr executor, const Target& target);

  virtual EffectType getType() const;

  virtual void load(const Params& params);
  virtual Params toParams() const;

  virtual int  getTime() const { return 0; }
  virtual void setTime(int) {}

  virtual std::string getName() const;

private:
  Damage _heal;
};

}

#endif // HEALEFFECT_H
