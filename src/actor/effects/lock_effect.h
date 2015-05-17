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

  virtual bool apply(ActorPtr executor, std::vector<ActorPtr> targets);
  virtual void load(const EffectDescription& dsc);
  virtual EffectDescription save();

private:
  int _lockId;

};

}

#endif // OPENEFFECT_H
