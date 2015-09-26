#ifndef DESTROYABLE_SERIALIZER_H
#define DESTROYABLE_SERIALIZER_H

#include <actor_feature_serializer.h>

namespace amarlon {

class DestroyableSerializer : public ActorFeatureSerializer
{
public:
  DestroyableSerializer();
  DestroyableSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~DestroyableSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // DESTROYABLE_SERIALIZER_H
