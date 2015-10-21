#ifndef SPELL_GATEWAY_H
#define SPELL_GATEWAY_H

#include <map>
#include <memory>
#include <vector>
#include <spell_parser.h>
#include <spell_id.h>
#include <character_classes.h>
#include <target_type.h>

namespace amarlon {

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class SpellDB
{
public:
  SpellDB();
  virtual ~SpellDB();

  virtual std::string getName(SpellId id);
  virtual int getLevel(SpellId id);
  virtual CharacterClass getClass(SpellId id);
  virtual TargetType getTargetType(SpellId id);
  virtual int getRange(SpellId id);
  virtual int getRadius(SpellId id);
  virtual std::string getDescription(SpellId id);
  std::string getScript(SpellId id) const;

  virtual SpellPtr fetch(SpellId id);
  virtual bool load(const std::string& fn);

protected:
  SpellParser _spellParser;
  std::map<SpellId, SpellDescriptionPtr> _spells;

  void parseSpells(std::vector<char> &buf);

};

}

#endif // SPELL_GATEWAY_H
