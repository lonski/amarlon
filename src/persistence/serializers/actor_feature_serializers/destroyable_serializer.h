#ifndef DESTROYABLE_SERIALIZER_H
#define DESTROYABLE_SERIALIZER_H

#include <memory>
#include <serializer.h>

namespace amarlon {

class DestroyableSerializer : public Serializer
{
public:
  DestroyableSerializer();
  DestroyableSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~DestroyableSerializer();

  virtual bool serialize(DescriptionPtr dsc);

};

}

#endif // DESTROYABLE_SERIALIZER_H
