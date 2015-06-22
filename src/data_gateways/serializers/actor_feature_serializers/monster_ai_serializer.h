#ifndef MONSTER_AI_SERIALIZE_H
#define MONSTER_AI_SERIALIZE_H

#include <memory>
#include <ai_serializer.h>

namespace amarlon {

class MonsterAiSerializer : public AiSerializer
{
public:
  MonsterAiSerializer();
  MonsterAiSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~MonsterAiSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // MONSTER_AI_SERIALIZE_H
