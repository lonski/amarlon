#include "destroyable_serializer.h"
#include <destroyable_description.h>
#include <utils.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

DestroyableSerializer::DestroyableSerializer()
{
}

DestroyableSerializer::DestroyableSerializer(xml_document<> *document, xml_node<> *xmlNode)
  : Serializer(document, xmlNode)
{
}

DestroyableSerializer::~DestroyableSerializer()
{
}

bool DestroyableSerializer::serialize(DescriptionPtr dsc)
{
  DestroyableDescriptionPtr dDsc = std::dynamic_pointer_cast<DestroyableDescription>(dsc);
  if ( dDsc && _document && _xml )
  {
    xml_node<>* _destrNode = _document->allocate_node(node_element, "Destroyable");
    _xml->append_node( _destrNode );

    for ( DropRule rule : dDsc->dropRules )
    {
      xml_node<>* ruleNode = _document->allocate_node(node_element, "DropRule");
      _destrNode->append_node( ruleNode );

      addAttributeEnum( ruleNode, "dropActorId", rule.dropActorId );
      addAttribute    ( ruleNode, "amountMin",   rule.amountMin   );
      addAttribute    ( ruleNode, "amountMax",   rule.amountMax   );
      addAttribute    ( ruleNode, "chance",      rule.chance      );
    }

  }

  return dDsc != nullptr;

}

}

