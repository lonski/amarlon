#include "animation_serializer.h"
#include <xml_utils.h>
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
    addAttributeEnum( _animNode, "type", anim->getType() );

    Params params = anim->toParams();
    for ( auto& pair : params )
    {
      xml_node<>* pNode = createNode( _document, "P", pair.second );
      _animNode->append_node( pNode );
      addAttribute( pNode, "name", pair.first );
    }

  }

  return serialized;
}

}
