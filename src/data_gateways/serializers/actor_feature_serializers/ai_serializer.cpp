#include "ai_serializer.h"
#include <ai.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

AiSerializer::AiSerializer()
  : AiSerializer(nullptr, nullptr)
{
}

AiSerializer::AiSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
  : ActorFeatureSerializer(document, xmlNode)
{
}

AiSerializer::~AiSerializer()
{
}

bool AiSerializer::serialize(ActorFeaturePtr af)
{
  AiPtr ai = std::dynamic_pointer_cast<Ai>(af);
  if ( ai && _document && _xml )
  {
    rapidxml::xml_node<>* aiNode = nullptr;

    if ( ai->getAiType() == AiType::MonsterAi )
    {
      aiNode = createNode( _document, "MonsterAi", "");
    }
    else if ( ai->getAiType() == AiType::PlayerAi )
    {
      aiNode = createNode( _document, "PlayerAi", "");
    }
    if ( aiNode )
    {
      _xml->append_node( aiNode );
      addAttribute( aiNode, "script", ai->_scriptId );
    }
  }

  return ai != nullptr;
}

}

