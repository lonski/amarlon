#include "destroyable_serializer.h"
#include <destroyable.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

DestroyableSerializer::DestroyableSerializer()
{
}

DestroyableSerializer::DestroyableSerializer(xml_document<> *document, xml_node<> *xmlNode)
  : ActorFeatureSerializer(document, xmlNode)
{
}

DestroyableSerializer::~DestroyableSerializer()
{
}

bool DestroyableSerializer::serialize(ActorFeaturePtr af)
{
  DestroyablePtr destr = std::dynamic_pointer_cast<Destroyable>(af);
  if ( destr && _document && _xml )
  {
    xml_node<>* _destrNode = _document->allocate_node(node_element, "Destroyable");
    _xml->append_node( _destrNode );


    for ( DropRule rule : destr->getDropRules() )
    {
      xml_node<>* ruleNode = _document->allocate_node(node_element, "DropRule");
      _destrNode->append_node( ruleNode );

      addAttributeEnum( ruleNode, "dropActorId", rule.dropActorId );
      addAttribute    ( ruleNode, "amountMin",   rule.amountMin   );
      addAttribute    ( ruleNode, "amountMax",   rule.amountMax   );
      addAttribute    ( ruleNode, "chance",      rule.chance      );
    }

  }

  return destr != nullptr;
}

}
