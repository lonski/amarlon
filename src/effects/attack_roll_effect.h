#ifndef ATTACK_ROLL_EFFECT_H
#define ATTACK_ROLL_EFFECT_H

#include <memory>
#include <effect.h>

namespace amarlon {

class AttackRollEffect;
typedef std::shared_ptr<AttackRollEffect> AttackRollEffectPtr;

class AttackRollEffect : public Effect
                       , public std::enable_shared_from_this<AttackRollEffect>
{
public:
  AttackRollEffect();

  virtual EffectPtr clone();
  virtual bool isEqual(EffectPtr rhs);

  virtual bool apply(ActorPtr executor, const Target& target);
  virtual bool revoke(ActorPtr executor, const Target& target);

  virtual EffectType getType() const;

  virtual void load(const Params& params);
  virtual Params toParams() const;

  virtual int  getTime() const;
  virtual void setTime(int time);

private:
  int _time;
  int _modifier;

};

}
#endif // ATTACK_ROLL_EFFECT_H
