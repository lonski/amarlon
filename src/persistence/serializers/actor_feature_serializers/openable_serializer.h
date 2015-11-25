#ifndef OPENABLE_SERIALIZER_H
#define OPENABLE_SERIALIZER_H

#include <memory>
#include <actor_feature_serializer.h>

namespace amarlon {

class Openable;
typedef std::shared_ptr<Openable> OpenablePtr;

class OpenableSerializer : public ActorFeatureSerializer
{
public:
  OpenableSerializer();
  OpenableSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~OpenableSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // OPENABLE_SERIALIZER_H
