#include "pickable_serializer.h"
#include <pickable_description.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

PickableSerializer::PickableSerializer()
{
}

PickableSerializer::PickableSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : Serializer(document, xmlNode)
{
}

PickableSerializer::~PickableSerializer()
{
}

bool PickableSerializer::serialize(DescriptionPtr dsc)
{
  PickableDescriptionPtr pDsc = std::dynamic_pointer_cast<PickableDescription>(dsc);
  if ( pDsc && _document && _xml )
  {
    if ( pDsc->any() )
    {
      xml_node<>* _pickableNode = nullptr;

      if ( ScrollDescriptionPtr sDsc = std::dynamic_pointer_cast<ScrollDescription>(dsc) )
      {
        _pickableNode = _document->allocate_node(node_element, "Scroll");
        addAttribute( _pickableNode, "spell", sDsc->spellId );
      }
      else
      {
        _pickableNode = _document->allocate_node(node_element, "Pickable");
      }

      _xml->append_node( _pickableNode );

      if ( pDsc->scriptId )      addAttribute( _pickableNode, "scriptId",   *pDsc->scriptId );
      if ( pDsc->stackable )     addAttribute( _pickableNode, "stackable",  *pDsc->stackable );
      if ( pDsc->amount )        addAttribute( _pickableNode, "amount",     *pDsc->amount );
      if ( pDsc->armorClass )    addAttribute( _pickableNode, "armorClass", *pDsc->armorClass );
      if ( pDsc->weight )        addAttribute( _pickableNode, "weight",     *pDsc->weight );
      if ( pDsc->price )         addAttribute( _pickableNode, "price",      *pDsc->price );
      if ( pDsc->damage )        addAttribute( _pickableNode, "damage",     *pDsc->damage );
      if ( pDsc->uses )          addAttribute( _pickableNode, "uses",       *pDsc->uses );
      if ( pDsc->range )         addAttribute( _pickableNode, "range",      *pDsc->range );
      if ( pDsc->radius )        addAttribute( _pickableNode, "radius",     *pDsc->radius );
      if ( pDsc->itemSlot )      addAttribute( _pickableNode, "itemSlot",   *pDsc->itemSlot );
      if ( pDsc->targetType )    addAttribute( _pickableNode, "targetType", *pDsc->targetType );
      if ( pDsc->armorType )     addAttribute( _pickableNode, "armorType",     *pDsc->armorType );
      if ( pDsc->weaponType )    addAttribute( _pickableNode, "weaponType",    *pDsc->weaponType );
      if ( pDsc->amunitionType ) addAttribute( _pickableNode, "amunitionType", *pDsc->amunitionType );
      if ( pDsc->category )      addAttribute( _pickableNode, "category",      *pDsc->category );
    }
  }

  return pDsc != nullptr;
}

}
