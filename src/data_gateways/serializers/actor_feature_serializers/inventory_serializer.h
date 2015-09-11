#ifndef CONTAINER_SERIALIZER_H
#define CONTAINER_SERIALIZER_H

#include <memory>
#include <actor_feature_serializer.h>

namespace amarlon {

class InventorzSerializer : public ActorFeatureSerializer
{
public:
  InventorzSerializer();
  InventorzSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~InventorzSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // CONTAINER_SERIALIZER_H
