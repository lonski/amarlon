#ifndef PICKABLE_SERIALIZER_H
#define PICKABLE_SERIALIZER_H

#include <actor_feature_serializer.h>

namespace amarlon {

class PickableSerializer : public ActorFeatureSerializer
{
public:
  PickableSerializer();
  PickableSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~PickableSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // PICKABLE_SERIALIZER_H
