#ifndef TALKER_SERIALIZER_H
#define TALKER_SERIALIZER_H

#include <serializer.h>

namespace amarlon {

class TalkerSerializer : public Serializer
{
public:
  TalkerSerializer();
  TalkerSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~TalkerSerializer();

  virtual bool serialize(DescriptionPtr dsc);

};

}

#endif // TALKER_SERIALIZER_H
