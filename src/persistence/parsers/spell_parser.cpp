#include "spell_parser.h"
#include <xml_utils.h>

namespace amarlon {

SpellParser::SpellParser(rapidxml::xml_node<> *xmlNode)
  : Parser(xmlNode)
{
}

SpellDescriptionPtr SpellParser::parseSpellDsc()
{
  SpellDescriptionPtr spellDsc;

  if ( _xml != nullptr)
  {
    spellDsc.reset( new SpellDescription );

    spellDsc->name = getAttribute<std::string>(_xml, "name");
    spellDsc->description = getAttribute<std::string>(_xml, "description");
    spellDsc->level = getAttribute<int>(_xml, "level");
    spellDsc->spellClass = getAttribute<int>(_xml, "class");
    spellDsc->targetType = getAttribute<int>(_xml, "targetType");
    spellDsc->range = getAttribute<int>(_xml, "range");
    spellDsc->radius = getAttribute<int>(_xml, "radius");
    spellDsc->id = getAttribute<int>(_xml, "id");
  }

  return spellDsc;
}

}

