#include "effect_serializer.h"
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

    _effectNode->append_attribute( _document->allocate_attribute(
                                       "type",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(effect->getType())
                                                                     ).c_str()) ) );

    Params params = effect->toParams();
    for ( auto& pair : params )
    {
      xml_node<>* pNode = _document->allocate_node(node_element, "P", _document->allocate_string(pair.second.c_str()) );
      pNode->append_attribute( _document->allocate_attribute("name", _document->allocate_string(pair.first.c_str())));
      _effectNode->append_node( pNode );
    }

  }

  return serialized;
}

}
