#ifndef OPENABLE_CONTAINER_SERIALIZER_H
#define OPENABLE_CONTAINER_SERIALIZER_H

#include <memory>
#include <openable_serializer.h>

namespace amarlon {

class OpenableInventorySerializer : public OpenableSerializer
{
public:
  OpenableInventorySerializer();
  OpenableInventorySerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~OpenableInventorySerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // OPENABLE_CONTAINER_SERIALIZER_H
