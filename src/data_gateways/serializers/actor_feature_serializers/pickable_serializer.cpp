#include "pickable_serializer.h"
#include <pickable.h>
#include <utils.h>

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

    _pickableNode->append_attribute( _document->allocate_attribute(
                                       "stackable",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(pickable->isStackable())
                                                                     ).c_str()) ) );

    _pickableNode->append_attribute( _document->allocate_attribute(
                                       "amount",
                                       _document->allocate_string( toStr( pickable->getAmount() ).c_str()) ) );

    _pickableNode->append_attribute( _document->allocate_attribute(
                                       "itemSlot",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(pickable->getItemSlot())
                                                                     ).c_str()) ) );

    _pickableNode->append_attribute( _document->allocate_attribute(
                                       "category",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(pickable->getCategory())
                                                                     ).c_str()) ) );

    _pickableNode->append_attribute( _document->allocate_attribute(
                                       "armorClass",
                                       _document->allocate_string( toStr( pickable->getArmorClass() ).c_str()) ) );

    _pickableNode->append_attribute( _document->allocate_attribute(
                                       "weight",
                                       _document->allocate_string( toStr( pickable->getWeight() ).c_str()) ) );

    _pickableNode->append_attribute( _document->allocate_attribute(
                                       "price",
                                       _document->allocate_string( toStr( pickable->getPrice() ).c_str()) ) );

    _pickableNode->append_attribute( _document->allocate_attribute(
                                       "damageDice",
                                       _document->allocate_string(
                                         (toStr( pickable->getDiceCount() )
                                          + "d"
                                          + toStr(static_cast<int>(pickable->getDamageDice()))
                                          ).c_str()) ) );

    _pickableNode->append_attribute( _document->allocate_attribute(
                                       "uses",
                                       _document->allocate_string( toStr( pickable->getUsesCount()  ).c_str()) ) );

    _pickableNode->append_attribute( _document->allocate_attribute(
                                       "targetType",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(pickable->getTargetType())
                                                                     ).c_str()) ) );
    _effectSerializer.setDestination(_document, _pickableNode);
    _effectSerializer.serialize( pickable->getEffect() );
  }

  return pickable != nullptr;
}

}

