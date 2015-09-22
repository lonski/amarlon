#ifndef SAVING_THROW_MODIFY_EFFECT_H
#define SAVING_THROW_MODIFY_EFFECT_H

#include <memory>
#include <effect.h>
#include <saving_throws_table.h>

namespace amarlon {

class SavingThrowModifyEffect;
typedef std::shared_ptr<SavingThrowModifyEffect> SavingThrowModifyEffectPtr;

class SavingThrowModifyEffect : public Effect
                              , public std::enable_shared_from_this<SavingThrowModifyEffect>
{
public:
  SavingThrowModifyEffect();

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
  SavingThrows::Type _type;

};

}

#endif // SAVING_THROW_MODIFY_EFFECT_H
