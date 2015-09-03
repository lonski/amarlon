#include "spell_gateway.h"
#include <fstream>
#include <vector>
#include <spell.h>
#include <xml/rapidxml_print.hpp>
#include <xml/rapidxml.hpp>
#include <spell_serializer.h>

namespace amarlon {

SpellGateway::SpellGateway()
{
}

SpellGateway::~SpellGateway()
{
}

SpellPtr SpellGateway::fetch(SpellId id)
{
  SpellPtr spell;

  auto sIter = _spells.find(id);
  if ( sIter != _spells.end() )
  {
    spell = sIter->second->clone();
  }

  return spell;
}

bool SpellGateway::load(const std::string &fn)
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

bool SpellGateway::store(const std::string& fn)
{
  std::ofstream ofs(fn);
  if ( ofs.is_open() )
  {
    ofs << *serializeSpells();
    return true;
  }
  return false;
}

void SpellGateway::parseSpells(std::vector<char> &buf)
{
  rapidxml::xml_document<> doc;
  doc.parse<0>(&buf[0]);

  rapidxml::xml_node<>* spells    = doc.first_node("Spells");
  rapidxml::xml_node<>* spellNode = spells ? spells->first_node("Spell") : nullptr;

  while(spellNode != nullptr)
  {
    _spellParser.setSource( spellNode );
    SpellPtr spell = Spell::create( _spellParser.parseSpellDsc() );
    if ( spell ) _spells[ spell->getId() ] = spell;

    spellNode = spellNode->next_sibling();
  }

}

std::shared_ptr<rapidxml::xml_document<> > SpellGateway::serializeSpells()
{
  std::shared_ptr<rapidxml::xml_document<> > doc(new rapidxml::xml_document<>);

  rapidxml::xml_node<>* spellsNode = doc->allocate_node(rapidxml::node_element, "Spells");
  doc->append_node(spellsNode);

  SpellSerializer _spellSerializer(doc.get(), spellsNode);
  for (auto s : _spells) _spellSerializer.serialize( s.second );

  return doc;
}

}

