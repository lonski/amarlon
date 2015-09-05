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

    animDsc->type = (animation::Type)getAttribute<int>(_xml, "type");
    animDsc->color = strToColor( getAttribute<std::string>(_xml, "color") );
  }

  return animDsc;
}

}

