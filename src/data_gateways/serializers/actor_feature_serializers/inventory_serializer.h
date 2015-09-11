#ifndef CONTAINER_SERIALIZER_H
#define CONTAINER_SERIALIZER_H

#include <memory>
#include <actor_feature_serializer.h>

namespace amarlon {

class InventorySerializer : public ActorFeatureSerializer
{
public:
  InventorySerializer();
  InventorySerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~InventorySerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // CONTAINER_SERIALIZER_H
