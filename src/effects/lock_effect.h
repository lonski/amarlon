#ifndef OPENEFFECT_H
#define OPENEFFECT_H

#include <memory>
#include <effect.h>

namespace amarlon {

class LockEffect;
typedef std::shared_ptr<LockEffect> LockEffectPtr;

class LockEffect : public Effect
{
public:
  LockEffect();

  virtual EffectPtr clone();
  virtual bool isEqual(EffectPtr rhs);

  virtual bool apply(ActorPtr executor, const Target& target);
  virtual void load(EffectDescriptionPtr dsc);
  virtual EffectDescriptionPtr save();

  virtual EffectType getType() const;
  virtual int getLockId() const;

private:
  int _lockId;

};

}

#endif // OPENEFFECT_H
