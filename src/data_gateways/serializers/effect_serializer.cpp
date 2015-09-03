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

    //TODO: the effect will be reworked in the right way. at the momment a workaround serialization
    LockEffectPtr lock = std::dynamic_pointer_cast<LockEffect>(effect);
    if ( lock )
    {
      _effectNode->append_attribute( _document->allocate_attribute(
                                         "lockId",
                                         _document->allocate_string( toStr( lock->getLockId()  ).c_str()) ) );
    }

    HealEffectPtr heal = std::dynamic_pointer_cast<HealEffect>(effect);
    if ( heal )
    {
      _effectNode->append_attribute( _document->allocate_attribute(
                                         "heal",
                                         _document->allocate_string( toStr( heal->getHealAmount()  ).c_str()) ) );
    }
  }

  return serialized;
}

}
