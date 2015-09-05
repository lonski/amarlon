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


    Params params = anim->toParams();
    for ( auto& pair : params )
    {
      xml_node<>* pNode = _document->allocate_node(node_element, "P", _document->allocate_string(pair.second.c_str()) );
      pNode->append_attribute( _document->allocate_attribute("name", _document->allocate_string(pair.first.c_str())));
      _animNode->append_node( pNode );
    }

  }

  return serialized;
}

}
