#include "effect_serializer.h"
#include <xml_utils.h>
#include <effect.h>
#include <lock_effect.h>
#include <heal_effect.h>
#include <utils.h>

using namespace rapidxml;

namespace amarlon {

EffectSerializer::EffectSerializer()
{
}

EffectSerializer::EffectSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : Serializer(document, xmlNode)
{
}

EffectSerializer::~EffectSerializer()
{
}

bool EffectSerializer::serialize(EffectPtr effect)
{
  bool serialized = false;

  if ( effect && _document && _xml )
  {
    xml_node<>* _effectNode = _document->allocate_node(node_element, "Effect");
    _xml->append_node( _effectNode );
    addAttributeEnum( _effectNode, "type", effect->getType() );
    addAttribute( _effectNode, "time", effect->getTime() );

    Params params = effect->toParams();
    for ( auto& pair : params )
    {
      xml_node<>* pNode = createNode( _document, "P", pair.second );
      _effectNode->append_node( pNode );
      addAttribute( pNode, "name", pair.first );
    }

  }

  return serialized;
}

}
