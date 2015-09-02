#ifndef EFFECT_H
#define EFFECT_H

#include <memory>
#include <vector>
#include <effect_type.h>
#include <actor_descriptions.h>
#include <target.h>

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

  virtual bool apply(ActorPtr executor, const Target& target) = 0;
  virtual void load(const EffectDescription& dsc) = 0;
  virtual EffectDescription save() = 0;

  virtual EffectType getType() const = 0;

};

}

#endif // EFFECT_H
