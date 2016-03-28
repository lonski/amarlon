#ifndef ACTOR_FEATURE_SERIALIZER
#define ACTOR_FEATURE_SERIALIZER

#include <memory>
#include <serializer.h>

namespace amarlon {

class ActorFeature;
typedef std::shared_ptr<ActorFeature> ActorFeaturePtr;

class ActorFeatureSerializer : public Serializer
{
public:
  ActorFeatureSerializer() {}
  ActorFeatureSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
    : Serializer(document, xmlNode)
  {}
  virtual ~ActorFeatureSerializer() {}

  virtual bool serialize(ActorFeaturePtr af) = 0;

};

typedef std::shared_ptr<ActorFeatureSerializer> ActorFeatureSerializerPtr;

}

#endif // ACTOR_FEATURE_SERIALIZER

