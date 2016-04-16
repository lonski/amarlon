#include "spell_db.h"
#include <fstream>
#include <vector>
#include <spell.h>
#include <engine.h>
#include <module.h>
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
    parseSpells(buf, _spells);

    return true;
  }
  return false;
}

bool SpellDB::loadPlugin(const std::string &fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buf.push_back('\0');
    parseSpells(buf, _pluginSpells);

    return true;
  }
  return false;
}

void SpellDB::parseSpells(std::vector<char> &buf, std::map<SpellId, SpellDescriptionPtr> &dst)
{
  rapidxml::xml_document<> doc;
  doc.parse<0>(&buf[0]);

  rapidxml::xml_node<>* spells    = doc.first_node("Spells");
  rapidxml::xml_node<>* spellNode = spells ? spells->first_node("Spell") : nullptr;

  while(spellNode != nullptr)
  {
    _spellParser.setSource( spellNode );
    SpellDescriptionPtr dsc = _spellParser.parseSpellDsc();
    if ( dsc ) dst[ static_cast<SpellId>(dsc->id) ] = dsc;

    spellNode = spellNode->next_sibling();
  }

}

std::vector<SpellDescriptionPtr> SpellDB::getMergedSpells()
{
  std::vector<SpellDescriptionPtr> spells;

  for ( auto& kv : _pluginSpells )
  {
    spells.push_back(kv.second);
  }

  for ( auto& kv : _spells )
  {
    if ( _pluginSpells.find(kv.first) == _pluginSpells.end() )
      spells.push_back(kv.second);
  }

  return spells;
}

SpellDescriptionPtr SpellDB::fetchDescription(SpellId id) const
{
  auto it = _pluginSpells.find(id);
  if ( it != _pluginSpells.end() )
    return it->second;

  it = _spells.find(id);
  if ( it != _spells.end() )
    return it->second;

  return nullptr;
}

std::string amarlon::SpellDB::getName(SpellId id)
{
  auto d = fetchDescription(id);
  return d ? d->name : "";
}

int SpellDB::getLevel(SpellId id)
{
  auto d = fetchDescription(id);
  return d ? d->level : 0;
}

CharacterClassType SpellDB::getClass(SpellId id)
{
  auto d = fetchDescription(id);
  return d ? static_cast<CharacterClassType>(d->spellClass) : CharacterClassType::NoClass;
}

TargetType SpellDB::getTargetType(SpellId id)
{
  auto d = fetchDescription(id);
  return d ? static_cast<TargetType>(d->targetType) : TargetType::SELF;
}

int SpellDB::getRange(SpellId id)
{
  auto d = fetchDescription(id);
  return d ? d->range : 0;
}

int SpellDB::getRadius(SpellId id)
{
  auto d = fetchDescription(id);
  return d ? d->radius : 0;
}

std::string SpellDB::getDescription(SpellId id)
{
  auto d = fetchDescription(id);
  return d ? d->description : "";
}

std::string SpellDB::getScript(SpellId id) const
{
  std::string default_script = "scripts/spells/" + std::to_string( static_cast<int>(id) ) + ".lua";
  std::string module_script = Engine::instance().getModule().getPath() + default_script;

  return file_exists(module_script) ? module_script : default_script;
}

std::vector<SpellPtr> SpellDB::getSpells(std::function<bool (SpellPtr)> filter)
{
  std::vector<SpellPtr> spells;

  for ( auto dsc : getMergedSpells() )
  {
    auto s = fetch( static_cast<SpellId>(dsc->id) );
    if ( filter(s) ) spells.push_back(s);
  }

  return spells;
}

SpellPtr SpellDB::fetch(SpellId id)
{
  SpellPtr spell;

  if ( id != SpellId::Null )
  {
    spell.reset(new Spell(id));

    auto it = _pluginSpells.find(id);
    if ( it != _pluginSpells.end() )
    {
      spell->_flyweight = it->second;
    }
    else
    {
      it = _spells.find(id);
      spell->_flyweight = it != _spells.end() ? it->second : nullptr;
    }

  }

  return spell;
}

}

