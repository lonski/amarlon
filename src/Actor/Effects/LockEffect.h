#ifndef OPENEFFECT_H
#define OPENEFFECT_H

#include "Effect.h"

namespace amarlon {

class LockEffect : public Effect
{
public:
  LockEffect();

  virtual Effect* clone();
  virtual bool isEqual(Effect *rhs);

  virtual bool apply(Actor* executor, std::vector<Actor*> targets);
  virtual void load(const EffectDescription& dsc);
  virtual EffectDescription save();

private:
  int _lockId;

};

}

#endif // OPENEFFECT_H
