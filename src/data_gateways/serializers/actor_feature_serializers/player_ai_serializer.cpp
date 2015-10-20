#include "player_ai_serializer.h"
#include <player_ai.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

PlayerAiSerializer::PlayerAiSerializer()
  : PlayerAiSerializer(nullptr, nullptr)
{
}

PlayerAiSerializer::PlayerAiSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : AiSerializer(document, xmlNode)
{
}

PlayerAiSerializer::~PlayerAiSerializer()
{
}

bool PlayerAiSerializer::serialize(ActorFeaturePtr af)
{
  PlayerAiPtr pAi = std::dynamic_pointer_cast<PlayerAi>(af);
  if ( pAi && _document && _xml )
  {
    _xml->append_node( createNode( _document, "PlayerAi", "") );
  }

  return pAi != nullptr;
}

}

