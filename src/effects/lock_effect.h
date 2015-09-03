#ifndef OPENEFFECT_H
#define OPENEFFECT_H

#include "effect.h"

namespace amarlon {

class LockEffect : public Effect
{
public:
  LockEffect();

  virtual Effect* clone();
  virtual bool isEqual(Effect *rhs);

  virtual bool apply(ActorPtr executor, const Target& target);
  virtual void load(const EffectDescription& dsc);
  virtual EffectDescription save();

  virtual EffectType getType() const;
  virtual int getLockId() const;

private:
  int _lockId;

};

}

#endif // OPENEFFECT_H
