#ifndef AI_SERIALIZER_H
#define AI_SERIALIZER_H

#include <memory>
#include <serializer.h>

namespace amarlon {

class Ai;
typedef std::shared_ptr<Ai> AiPtr;

class AiSerializer : public Serializer
{
public:
  AiSerializer();
  AiSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~AiSerializer();

  virtual bool serialize(DescriptionPtr dsc);

};

}
#endif // AI_SERIALIZER_H
