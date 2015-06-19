#ifndef ACTOR_SERIALIZER_H
#define ACTOR_SERIALIZER_H

#include <memory>
#include <serializer.h>

namespace amarlon {

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

class ActorSerializer : public Serializer
{
public:
  ActorSerializer();
  ActorSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~ActorSerializer();

  virtual bool serialize(ActorPtr actor);

private:
  rapidxml::xml_node<>* _actorNode;

};

}

#endif // ACTOR_SERIALIZER_H
