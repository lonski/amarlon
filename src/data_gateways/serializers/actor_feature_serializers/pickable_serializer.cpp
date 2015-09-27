#include "pickable_serializer.h"
#include <pickable.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

PickableSerializer::PickableSerializer()
{
}

PickableSerializer::PickableSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : ActorFeatureSerializer(document, xmlNode)
{
}

PickableSerializer::~PickableSerializer()
{
}

bool PickableSerializer::serialize(ActorFeaturePtr af)
{
  PickablePtr pickable = std::dynamic_pointer_cast<Pickable>(af);
  if ( pickable && _document && _xml )
  {
    xml_node<>* _pickableNode = _document->allocate_node(node_element, "Pickable");
    _xml->append_node( _pickableNode );

    addAttribute    ( _pickableNode, "id",         pickable->getScriptId() );
    addAttribute    ( _pickableNode, "stackable",  static_cast<int>(pickable->isStackable()) );
    addAttribute    ( _pickableNode, "amount",     pickable->getAmount() );
    addAttribute    ( _pickableNode, "armorClass", pickable->getArmorClass() );
    addAttribute    ( _pickableNode, "weight",     pickable->getWeight() );
    addAttribute    ( _pickableNode, "price",      pickable->getPrice() );
    addAttribute    ( _pickableNode, "damage",     std::string(pickable->getDamage()) );
    addAttribute    ( _pickableNode, "uses",       pickable->getUsesCount() );
    addAttributeEnum( _pickableNode, "itemSlot",   pickable->getItemSlot() );
    addAttributeEnum( _pickableNode, "category",   pickable->getCategory() );
    addAttributeEnum( _pickableNode, "targetType", pickable->getTargetType() );
  }

  return pickable != nullptr;
}

}

