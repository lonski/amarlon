#ifndef TRAP_SERIALIZER_H
#define TRAP_SERIALIZER_H

#include <serializer.h>

namespace amarlon {

class Trap;
typedef std::shared_ptr<Trap> TrapPtr;

class TrapSerializer : public Serializer
{
public:
  TrapSerializer();
  TrapSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~TrapSerializer();

  virtual bool serialize(DescriptionPtr dsc);

};

}

#endif // TRAP_SERIALIZER_H
