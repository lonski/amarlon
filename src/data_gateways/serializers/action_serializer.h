#ifndef ACTION_SERIALIZER_H
#define ACTION_SERIALIZER_H

#include <memory>
#include <serializer.h>

namespace amarlon {

class ActorAction;
typedef std::shared_ptr<ActorAction> ActorActionPtr;

class ActionSerializer : public Serializer
{
public:
  ActionSerializer();
  ActionSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* parentNode);
  ~ActionSerializer();

  bool serialize(ActorActionPtr action);

};

}

#endif // ACTION_SERIALIZER_H
