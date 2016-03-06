#ifndef SPELL_H
#define SPELL_H

#include <memory>
#include <target.h>
#include <character_class_type.h>
#include <target_type.h>
#include <spell_id.h>
#include <spell.pb.h>

namespace amarlon {

class Actor;
class Spell;
class SpellData;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Spell> SpellPtr;

class Spell
{
public:
  Spell(const SpellData& data);
  Spell(const Spell& spell);
  static SpellPtr create(SpellId id);

  SpellPtr clone() const;
  Spell& operator=(const Spell& spell);
  bool operator==(const Spell& rhs);

  virtual ~Spell();

  virtual bool cast(ActorPtr caster, Target target);

  virtual SpellId getId() const;
  virtual std::string getName() const;
  virtual CharacterClassType getClass() const;
  virtual int getLevel() const;
  virtual TargetType getTargetType() const;
  virtual int getRange() const;
  virtual int getRadius() const;
  virtual std::string getDescription() const;
  std::string getScript() const;

private:
  SpellData _data;

};

}

#endif // SPELL_H
