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
class Spell;
typedef std::shared_ptr<Actor>  ActorPtr;
typedef std::shared_ptr<Spell>  SpellPtr;

class Spell
{
public:

  virtual ~Spell();

  static SpellPtr create(SpellId id);

  virtual SpellPtr clone();

  virtual bool cast(ActorPtr caster, Target target);

  virtual SpellId getId() const;
  virtual std::string getName() const;
  virtual CharacterClass getClass() const;
  virtual int getLevel() const;
  virtual TargetType getTargetType() const;
  virtual int getRange() const;
  virtual int getRadius() const;
  virtual std::string getDescription() const;
  std::string getScript() const;

  bool operator==(const Spell& rhs);

private:
  SpellId _id;
  SpellDescriptionPtr _flyweight;

  Spell(SpellId id);

  friend class SpellSerializer;
  friend class SpellDB;
};

}

#endif // SPELL_H
