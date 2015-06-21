#ifndef OPENABLE_DOOR_SERIALIZER_H
#define OPENABLE_DOOR_SERIALIZER_H

#include <memory>
#include <openable_serializer.h>

namespace amarlon {

class OpenableDoorSerializer : public OpenableSerializer
{
public:
  OpenableDoorSerializer();
  OpenableDoorSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~OpenableDoorSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // OPENABLE_DOOR_SERIALIZER_H
