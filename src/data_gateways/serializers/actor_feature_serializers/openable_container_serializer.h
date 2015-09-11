#ifndef OPENABLE_CONTAINER_SERIALIZER_H
#define OPENABLE_CONTAINER_SERIALIZER_H

#include <memory>
#include <openable_serializer.h>

namespace amarlon {

class OpenableInventorzSerializer : public OpenableSerializer
{
public:
  OpenableInventorzSerializer();
  OpenableInventorzSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~OpenableInventorzSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // OPENABLE_CONTAINER_SERIALIZER_H
