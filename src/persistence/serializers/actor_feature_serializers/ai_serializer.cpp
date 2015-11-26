#include "ai_serializer.h"
#include <ai_description.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

AiSerializer::AiSerializer()
  : AiSerializer(nullptr, nullptr)
{
}

AiSerializer::AiSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  : Serializer(document, xmlNode)
{
}

AiSerializer::~AiSerializer()
{
}

bool AiSerializer::serialize(DescriptionPtr dsc)
{
  bool serialized = false;
  AiDescriptionPtr ai = std::dynamic_pointer_cast<AiDescription>(dsc);
  if ( ai && _document && _xml )
  {
    serialized = true;
    rapidxml::xml_node<>* aiNode = nullptr;

    if ( ai->type )
    {
      if ( *ai->type == 1 )
      {
        aiNode = createNode( _document, "Ai", "");
      }
      else
      {
        aiNode = createNode( _document, "PlayerAi", "");
      }
      _xml->append_node( aiNode );
      if ( ai->script )
      {
        addAttribute( aiNode, "script", *ai->script );
      }
    }
  }

  return serialized;
}

}

