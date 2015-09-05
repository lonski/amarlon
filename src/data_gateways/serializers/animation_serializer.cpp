#include "animation_serializer.h"
#include <animation.h>
#include <blink.h>
#include <utils.h>

using namespace rapidxml;

namespace amarlon {

AnimationSerializer::AnimationSerializer()
{
}

AnimationSerializer::AnimationSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : Serializer(document, xmlNode)
{
}

AnimationSerializer::~AnimationSerializer()
{
}

bool AnimationSerializer::serialize(animation::AnimationPtr anim)
{
  bool serialized = false;

  if ( anim && _document && _xml )
  {
    xml_node<>* _animNode = _document->allocate_node(node_element, "Animation");
    _xml->append_node( _animNode );

    _animNode->append_attribute( _document->allocate_attribute(
                                       "type",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(anim->getType())
                                                                     ).c_str()) ) );

    //TODO: the effect will be reworked in the right way. at the momment a workaround serialization
    animation::BlinkPtr blink = std::dynamic_pointer_cast<animation::Blink>(anim);
    if ( blink )
    {
      _animNode->append_attribute( _document->allocate_attribute(
                                         "color",
                                         _document->allocate_string( colorToStr( blink->getTargetColor() ).c_str()  ) ) );
    }

  }

  return serialized;
}

}
