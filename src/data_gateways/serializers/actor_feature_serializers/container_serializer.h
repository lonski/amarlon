#ifndef CONTAINER_SERIALIZER_H
#define CONTAINER_SERIALIZER_H

#include <memory>
#include <actor_feature_serializer.h>

namespace amarlon {

class ContainerSerializer : public ActorFeatureSerializer
{
public:
  ContainerSerializer();
  ContainerSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~ContainerSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // CONTAINER_SERIALIZER_H
