#ifndef ACTOR_SERIALIZER_H
#define ACTOR_SERIALIZER_H

#include <memory>
#include <vector>
#include <serializer.h>
#include <actor_feature_serializer.h>

namespace amarlon {

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

class ActorSerializer : public Serializer
{
public:
  ActorSerializer();
  ActorSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~ActorSerializer();

  virtual bool serialize(ActorPtr actor, const char* nodeName = "Actor" );

private:
  rapidxml::xml_node<>* _actorNode;
  std::vector<ActorFeatureSerializerPtr> _afSerializers;

};

}

#endif // ACTOR_SERIALIZER_H
