#include "effect_parser.h"
#include <xml_utils.h>

namespace amarlon {

EffectParser::EffectParser(rapidxml::xml_node<> *xmlNode)
  : Parser(xmlNode)
{
}

EffectDescriptionPtr EffectParser::parseEffectDsc()
{
  EffectDescriptionPtr effectDsc;

  if ( _xml != nullptr)
  {
    effectDsc.reset( new EffectDescription );

    effectDsc->type = (EffectType)getAttribute<int>(_xml, "type");
    effectDsc->lockId = getAttribute<int>(_xml, "lockId");
    effectDsc->heal = getAttribute<int>(_xml, "heal");
  }

  return effectDsc;
}

}
