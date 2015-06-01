#ifndef EFFECT_H
#define EFFECT_H

#include <memory>
#include <vector>
#include <effect_type.h>
#include <actor_descriptions.h>
#include <target_type.h>

namespace amarlon {

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

class Effect
{
public:
  Effect();
  virtual ~Effect();

  static Effect* create(EffectType type);
  static Effect* create(const EffectDescription& dsc);
  virtual Effect* clone() = 0;
  virtual bool isEqual(Effect* rhs) = 0;

  virtual bool apply(ActorPtr executor, std::vector<ActorPtr> targets) = 0;
  virtual void load(const EffectDescription& dsc) = 0;
  virtual EffectDescription save() = 0;

  virtual TargetType getTargetType() const = 0;
  virtual int getUsesCount() const;

protected:
  int _usesCount;

};

}

#endif // EFFECT_H
