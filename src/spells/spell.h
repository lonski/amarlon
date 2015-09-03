#ifndef SPELL_H
#define SPELL_H

#include <memory>
#include <target.h>
#include <character_classes.h>
#include <target_type.h>
#include <spell_description.h>

namespace amarlon {

class Actor;
class Effect;
class Spell;
typedef std::shared_ptr<Actor>  ActorPtr;
typedef std::shared_ptr<Effect> EffectPtr;
typedef std::shared_ptr<Spell>  SpellPtr;

class Spell
{
public:

  Spell();
  virtual ~Spell();

  static SpellPtr create(SpellDescriptionPtr dsc);

  virtual bool cast(ActorPtr caster, Target target);

  virtual std::string getName() const;
  virtual CharacterClass getClass() const;
  virtual int getLevel() const;
  virtual TargetType getTargetType() const;

private:
  std::string _name;
  CharacterClass _class;
  int _level;
  TargetType _targetType;

  std::vector<EffectPtr> _effects;

};

}

#endif // SPELL_H
