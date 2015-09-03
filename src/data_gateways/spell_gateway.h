#ifndef SPELL_GATEWAY_H
#define SPELL_GATEWAY_H

#include <map>
#include <memory>
#include <spell_parser.h>
#include <spell_id.h>

namespace amarlon {

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class SpellGateway
{
public:
  SpellGateway();
  virtual ~SpellGateway();

  virtual SpellPtr fetch(SpellId id);
  virtual bool load(const std::string& fn);
  virtual bool store(const std::string& fn);

protected:
  SpellParser _spellParser;
  std::map<SpellId, SpellPtr> _spells;

  void parseSpells(std::vector<char> &buf);
  std::shared_ptr<rapidxml::xml_document<> > serializeSpells();

};

}

#endif // SPELL_GATEWAY_H
