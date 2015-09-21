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

    if ( attributeExists( _xml, "time") )
      effectDsc->time = getAttribute<int>(_xml, "time");
    else
      effectDsc->time = -1;

    rapidxml::xml_node<>* pNode = _xml->first_node("P");
    while( pNode )
    {
      effectDsc->params[ getAttribute<std::string>(pNode, "name") ] = pNode->value();
      pNode = pNode->next_sibling();
    }

  }

  return effectDsc;
}

}
