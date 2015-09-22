#ifndef MORALE_MODIFY_EFFECT_H
#define MORALE_MODIFY_EFFECT_H

#include <memory>
#include <effect.h>

namespace amarlon {

class MoraleModifyEffect;
typedef std::shared_ptr<MoraleModifyEffect> MoraleModifyEffectPtr;

class MoraleModifyEffect : public Effect
                         , public std::enable_shared_from_this<MoraleModifyEffect>
{
public:
  MoraleModifyEffect();

  virtual EffectPtr clone();
  virtual bool isEqual(EffectPtr rhs);

  virtual bool apply(ActorPtr executor, const Target& target);
  virtual bool revoke(ActorPtr executor, const Target& target);

  virtual EffectType getType() const;

  virtual void load(const Params& params);
  virtual Params toParams() const;

  virtual int  getTime() const;
  virtual void setTime(int time);

  virtual std::string getName() const;

private:
  int _time;
  int _modifier;

};

}

#endif // MORALE_MODIFY_EFFECT_H
