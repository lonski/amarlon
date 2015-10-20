#ifndef PLAYER_AI_SERIALIZER_H
#define PLAYER_AI_SERIALIZER_H

#include <memory>
#include <ai_serializer.h>

namespace amarlon {

class PlayerAiSerializer : public AiSerializer
{
public:
  PlayerAiSerializer();
  PlayerAiSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~PlayerAiSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // PLAYER_AI_SERIALIZER_H
