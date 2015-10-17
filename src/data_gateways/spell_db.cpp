#include "spell_db.h"
#include <fstream>
#include <vector>
#include <spell.h>
#include <xml/rapidxml_print.hpp>
#include <xml/rapidxml.hpp>

namespace amarlon {

SpellDB::SpellDB()
{
}

SpellDB::~SpellDB()
{
}

bool SpellDB::load(const std::string &fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buf.push_back('\0');
    parseSpells(buf);

    return true;
  }
  return false;
}

void SpellDB::parseSpells(std::vector<char> &buf)
{
  rapidxml::xml_document<> doc;
  doc.parse<0>(&buf[0]);

  rapidxml::xml_node<>* spells    = doc.first_node("Spells");
  rapidxml::xml_node<>* spellNode = spells ? spells->first_node("Spell") : nullptr;

  while(spellNode != nullptr)
  {
    _spellParser.setSource( spellNode );
    SpellDescriptionPtr dsc = _spellParser.parseSpellDsc();
    if ( dsc ) _spells[ static_cast<SpellId>(dsc->id) ] = dsc;

    spellNode = spellNode->next_sibling();
  }

}

std::string amarlon::SpellDB::getName(SpellId id)
{
  auto it = _spells.find(id);
  return it != _spells.end() ? it->second->name : "";
}

int SpellDB::getLevel(SpellId id)
{
  auto it = _spells.find(id);
  return it != _spells.end() ? it->second->level : 0;
}

CharacterClass SpellDB::getClass(SpellId id)
{
  auto it = _spells.find(id);
  return it != _spells.end() ? static_cast<CharacterClass>(it->second->spellClass) : CharacterClass::NoClass;
}

TargetType SpellDB::getTargetType(SpellId id)
{
  auto it = _spells.find(id);
  return it != _spells.end() ? static_cast<TargetType>(it->second->targetType) : TargetType::SELF;
}

int SpellDB::getRange(SpellId id)
{
  auto it = _spells.find(id);
  return it != _spells.end() ? it->second->range : 0;
}

int SpellDB::getRadius(SpellId id)
{
  auto it = _spells.find(id);
  return it != _spells.end() ? it->second->radius : 0;
}

std::string SpellDB::getDescription(SpellId id)
{
  auto it = _spells.find(id);
  return it != _spells.end() ? it->second->description : "";
}

SpellPtr SpellDB::fetch(SpellId id)
{
  SpellPtr spell;

  if ( id != SpellId::Null )
  {
    spell.reset(new Spell(id));
    auto it = _spells.find(id);
    spell->_flyweight = it != _spells.end() ? it->second : nullptr;
  }

  return spell;
}

}

