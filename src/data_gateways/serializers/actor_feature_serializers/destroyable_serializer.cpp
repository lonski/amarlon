#include "destroyable_serializer.h"
#include <destroyable.h>
#include <utils.h>

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

      ruleNode->append_attribute( _document->allocate_attribute(
                                       "dropActorId",
                                       _document->allocate_string( toStr(
                                                                     static_cast<int>(rule.dropActorId)
                                                                     ).c_str()) ) );
      ruleNode->append_attribute( _document->allocate_attribute(
                                       "amountMin",
                                       _document->allocate_string( toStr( rule.amountMin ).c_str()) ) );
      ruleNode->append_attribute( _document->allocate_attribute(
                                       "amountMax",
                                       _document->allocate_string( toStr( rule.amountMax ).c_str()) ) );
      ruleNode->append_attribute( _document->allocate_attribute(
                                       "chance",
                                       _document->allocate_string( toStr( rule.chance ).c_str()) ) );
    }

  }

  return destr != nullptr;
}

}
