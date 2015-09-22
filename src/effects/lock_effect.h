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
  virtual bool revoke(ActorPtr executor, const Target& target);

  virtual EffectType getType() const;
  virtual int getLockId() const;

  virtual void load(const Params& params);
  virtual Params toParams() const;

  virtual int  getTime() const { return 0; }
  virtual void setTime(int) {}

  virtual std::string getName() const;

private:
  int _lockId;

};

}

#endif // OPENEFFECT_H
