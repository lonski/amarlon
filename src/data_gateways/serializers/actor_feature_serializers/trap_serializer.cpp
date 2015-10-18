#include "trap_serializer.h"
#include <trap.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

TrapSerializer::TrapSerializer()
  : TrapSerializer(nullptr, nullptr)
{
}

TrapSerializer::TrapSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  : ActorFeatureSerializer(document, xmlNode)
{
}

TrapSerializer::~TrapSerializer()
{
}

bool TrapSerializer::serialize(ActorFeaturePtr af)
{
  TrapPtr trap = std::dynamic_pointer_cast<Trap>(af);
  if ( trap && _xml && _document )
  {
    xml_node<>* trapNode = _document->allocate_node(node_element, "Trap");
    _xml->append_node( trapNode );

    addAttribute( trapNode, "id",      static_cast<int>(trap->getId()) );
    addAttribute( trapNode, "armed",      static_cast<int>(trap->isArmed()) );
    addAttribute( trapNode, "difficulty", trap->getDifficulty() );
    return true;
  }
  return false;
}

}
