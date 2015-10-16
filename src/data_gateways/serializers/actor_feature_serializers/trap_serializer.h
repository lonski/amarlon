#ifndef TRAP_SERIALIZER_H
#define TRAP_SERIALIZER_H

#include <memory>
#include <actor_feature_serializer.h>

namespace amarlon {

class Trap;
typedef std::shared_ptr<Trap> TrapPtr;

class TrapSerializer : public ActorFeatureSerializer
{
public:
  TrapSerializer();
  TrapSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~TrapSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // TRAP_SERIALIZER_H
