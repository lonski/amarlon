#ifndef PICKABLE_SERIALIZER_H
#define PICKABLE_SERIALIZER_H

#include <serializer.h>

namespace amarlon {

class PickableSerializer : public Serializer
{
public:
  PickableSerializer();
  PickableSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~PickableSerializer();

  virtual bool serialize(DescriptionPtr dsc);

};

}

#endif // PICKABLE_SERIALIZER_H
