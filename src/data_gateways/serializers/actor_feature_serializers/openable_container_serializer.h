#ifndef OPENABLE_CONTAINER_SERIALIZER_H
#define OPENABLE_CONTAINER_SERIALIZER_H

#include <memory>
#include <openable_serializer.h>

namespace amarlon {

class OpenableContainerSerializer : public OpenableSerializer
{
public:
  OpenableContainerSerializer();
  OpenableContainerSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~OpenableContainerSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // OPENABLE_CONTAINER_SERIALIZER_H
