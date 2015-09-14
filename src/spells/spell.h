#ifndef SPELL_H
#define SPELL_H

#include <memory>
#include <target.h>
#include <character_classes.h>
#include <target_type.h>
#include <spell_description.h>
#include <spell_id.h>

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
  virtual int getRange() const;
  virtual int getRadius() const;
  virtual int getDuration() const;

private:
  std::string _name;
  CharacterClass _class;
  int _level;
  TargetType _targetType;
  SpellId _id;
  int _range;
  int _radius;
  int _duration;

  std::set< std::pair<int, std::vector<EffectPtr> > > _effects;
  animation::AnimationPtr _animation;

  std::vector<EffectPtr> getEffectsFor(ActorPtr actor);


  friend class SpellSerializer;
};

}

#endif // SPELL_H
