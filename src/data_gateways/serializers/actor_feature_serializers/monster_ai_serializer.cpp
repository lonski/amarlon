#include "monster_ai_serializer.h"
#include <monster_ai.h>
#include <xml_utils.h>

using namespace rapidxml;

namespace amarlon {

MonsterAiSerializer::MonsterAiSerializer()
  : MonsterAiSerializer(nullptr, nullptr)
{
}

MonsterAiSerializer::MonsterAiSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : AiSerializer(document, xmlNode)
{
}

MonsterAiSerializer::~MonsterAiSerializer()
{
}

bool MonsterAiSerializer::serialize(ActorFeaturePtr af)
{
  MonsterAiPtr mobAi = std::dynamic_pointer_cast<MonsterAi>(af);
  if ( mobAi && _document && _xml )
  {
    _xml->append_node( createNode( _document, "MonsterAi", "") );
  }

  return mobAi != nullptr;
}

}
