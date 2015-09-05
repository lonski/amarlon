#ifndef SPELL_H
#define SPELL_H

#include <memory>
#include <target.h>
#include <character_classes.h>
#include <target_type.h>
#include <spell_description.h>
#include <spell_id.h>
#include <spell_gateway.h>

namespace amarlon {

class Actor;
class Effect;
class Spell;
typedef std::shared_ptr<Actor>  ActorPtr;
typedef std::shared_ptr<Effect> EffectPtr;
typedef std::shared_ptr<Spell>  SpellPtr;

namespace animation {
  class Animation;
  typedef std::shared_ptr<Animation> AnimationPtr;
}

class Spell
{
public:

  static SpellGateway Gateway;

  Spell();
  virtual ~Spell();

  static SpellPtr create(SpellDescriptionPtr dsc);
  virtual SpellPtr clone();

  virtual bool cast(ActorPtr caster, Target target);

  virtual SpellId getId() const;
  virtual std::string getName() const;
  virtual CharacterClass getClass() const;
  virtual int getLevel() const;
  virtual TargetType getTargetType() const;

private:
  std::string _name;
  CharacterClass _class;
  int _level;
  TargetType _targetType;
  SpellId _id;

  std::vector<EffectPtr> _effects;
  animation::AnimationPtr _animation;


  friend class SpellSerializer;
};

}

#endif // SPELL_H
