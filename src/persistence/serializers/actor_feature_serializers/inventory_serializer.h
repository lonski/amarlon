#ifndef CONTAINER_SERIALIZER_H
#define CONTAINER_SERIALIZER_H

#include <serializer.h>

namespace amarlon {

class InventorySerializer : public Serializer
{
public:
  InventorySerializer();
  InventorySerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~InventorySerializer();

  virtual bool serialize(DescriptionPtr dsc);

};

}

#endif // CONTAINER_SERIALIZER_H
