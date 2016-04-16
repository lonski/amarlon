#ifndef SPELL_GATEWAY_H
#define SPELL_GATEWAY_H

#include <map>
#include <memory>
#include <vector>
#include <spell_parser.h>
#include <spell_id.h>
#include <character_class_type.h>
#include <target_type.h>

namespace amarlon {

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class SpellDB
{
public:
  SpellDB();
  ~SpellDB();

  std::string getName(SpellId id);
  int getLevel(SpellId id);
  CharacterClassType getClass(SpellId id);
  TargetType getTargetType(SpellId id);
  int getRange(SpellId id);
  int getRadius(SpellId id);
  std::string getDescription(SpellId id);
  std::string getScript(SpellId id) const;

  std::vector<SpellPtr> getSpells( std::function<bool(SpellPtr)> filter );
  SpellPtr fetch(SpellId id);
  bool load(const std::string& fn);
  bool loadPlugin(const std::string& fn);

protected:
  SpellParser _spellParser;
  std::map<SpellId, SpellDescriptionPtr> _spells;
  std::map<SpellId, SpellDescriptionPtr> _pluginSpells;

  void parseSpells(std::vector<char> &buf, std::map<SpellId, SpellDescriptionPtr>& dst);
  std::vector<SpellDescriptionPtr> getMergedSpells();
  SpellDescriptionPtr fetchDescription(SpellId id) const;

};

}

#endif // SPELL_GATEWAY_H
