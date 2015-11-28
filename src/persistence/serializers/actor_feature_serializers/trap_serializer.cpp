#include "trap_serializer.h"
#include <trap_description.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

TrapSerializer::TrapSerializer()
  : TrapSerializer(nullptr, nullptr)
{
}

TrapSerializer::TrapSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  : Serializer(document, xmlNode)
{
}

TrapSerializer::~TrapSerializer()
{
}

bool TrapSerializer::serialize(DescriptionPtr dsc)
{
  TrapDescriptionPtr tDsc = std::dynamic_pointer_cast<TrapDescription>(dsc);
  if ( tDsc && _xml && _document )
  {
    if ( tDsc->any() )
    {
      xml_node<>* trapNode = _document->allocate_node(node_element, "Trap");
      _xml->append_node( trapNode );

      if ( tDsc->id )         addAttribute( trapNode, "id",         *tDsc->id );
      if ( tDsc->armed )      addAttribute( trapNode, "armed",      (int)*tDsc->armed );
      if ( tDsc->detected )   addAttribute( trapNode, "detected",   (int)*tDsc->detected );
      if ( tDsc->difficulty ) addAttribute( trapNode, "difficulty", *tDsc->difficulty );
    }
    return true;
  }
  return false;
}

}
