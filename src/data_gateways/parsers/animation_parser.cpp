#include "animation_parser.h"
#include <xml_utils.h>
#include <utils/utils.h>

namespace amarlon {

AnimationParser::AnimationParser(rapidxml::xml_node<> *xmlNode)
  : Parser(xmlNode)
{
}

AnimationDescriptionPtr AnimationParser::parseAnimationDsc()
{
  AnimationDescriptionPtr animDsc;

  if ( _xml != nullptr)
  {
    animDsc.reset( new AnimationDescription );

    animDsc->type = getAttribute<int>(_xml, "type");

    rapidxml::xml_node<>* pNode = _xml->first_node("P");
    while( pNode )
    {
      animDsc->params[ getAttribute<std::string>(pNode, "name") ] = pNode->value();
      pNode = pNode->next_sibling();
    }
  }

  return animDsc;
}

}

