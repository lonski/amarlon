#ifndef WEARER_SERIALIZER_H
#define WEARER_SERIALIZER_H

#include <serializer.h>

namespace amarlon {

class WearerSerializer : public Serializer
{
public:
  WearerSerializer();
  WearerSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~WearerSerializer();

  virtual bool serialize(DescriptionPtr dsc);

};

}


#endif // WEARER_SERIALIZER_H
