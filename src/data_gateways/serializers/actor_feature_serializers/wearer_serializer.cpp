#include "wearer_serializer.h"
#include <wearer.h>
#include <actor_serializer.h>
#include <utils.h>

using namespace rapidxml;

namespace amarlon {

WearerSerializer::WearerSerializer()
  : WearerSerializer(nullptr, nullptr)  
{
}

WearerSerializer::WearerSerializer(xml_document<> *document, xml_node<> *xmlNode)
  : ActorFeatureSerializer(document, xmlNode)
  , _wearerNode(nullptr)
{
}

WearerSerializer::~WearerSerializer()
{
}

bool WearerSerializer::serialize(ActorFeaturePtr af)
{
  _wearer = std::dynamic_pointer_cast<Wearer>(af);
  if ( _wearer && _document && _xml )
  {
    _wearerNode = _document->allocate_node(node_element, "Wearer");
    _xml->append_node( _wearerNode );

    serializeItemSlots();
  }

  return _wearer != nullptr;
}

void WearerSerializer::serializeItemSlots()
{
  for ( auto slot : ItemSlotType() )
  {
    if ( _wearer->hasSlot(slot) )
    {
      xml_node<>* _slotNode = _document->allocate_node(node_element, "ItemSlot");
      _wearerNode->append_node( _slotNode );

      serializeItemSlotAttributes(slot, _slotNode);
      serializeEquippedItem(slot, _slotNode);
    }
  }
}

void WearerSerializer::serializeItemSlotAttributes(ItemSlotType slot, rapidxml::xml_node<>* slotNode)
{
  slotNode->append_attribute( _document->allocate_attribute(
                                     "type",
                                     _document->allocate_string( toStr(
                                                                   static_cast<int>(slot)
                                                                   ).c_str()) ) );
}

void WearerSerializer::serializeEquippedItem(ItemSlotType slot, xml_node<>* slotNode)
{
  ActorPtr equipped = _wearer->equipped(slot);
  if ( equipped )
  {
    ActorSerializer actorSerializer(_document, slotNode);
    actorSerializer.serialize(equipped, "Equipped");
  }
}

}
