#ifndef AI_SERIALIZER_H
#define AI_SERIALIZER_H

#include <memory>
#include <actor_feature_serializer.h>

namespace amarlon {

class Ai;
typedef std::shared_ptr<Ai> AiPtr;

class AiSerializer : public ActorFeatureSerializer
{
public:
  AiSerializer();
  AiSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~AiSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}
#endif // AI_SERIALIZER_H
