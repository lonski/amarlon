#ifndef OPENABLE_SERIALIZER_H
#define OPENABLE_SERIALIZER_H

#include <serializer.h>

namespace amarlon {

class OpenableSerializer : public Serializer
{
public:
  OpenableSerializer();
  OpenableSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~OpenableSerializer();

  virtual bool serialize(DescriptionPtr dsc);

};

}

#endif // OPENABLE_SERIALIZER_H
