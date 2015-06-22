#include "monster_ai_serializer.h"
#include <monster_ai.h>

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
    xml_node<>* _mobAiNode = _document->allocate_node(node_element, "MonsterAi");
    _xml->append_node( _mobAiNode );
  }

  return mobAi != nullptr;
}

}
