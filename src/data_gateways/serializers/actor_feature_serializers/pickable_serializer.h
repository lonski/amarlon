#ifndef PICKABLE_SERIALIZER_H
#define PICKABLE_SERIALIZER_H

#include <actor_feature_serializer.h>
#include <effect_serializer.h>

namespace amarlon {

class PickableSerializer : public ActorFeatureSerializer
{
public:
  PickableSerializer();
  PickableSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~PickableSerializer();

  virtual bool serialize(ActorFeaturePtr af);

private:
  EffectSerializer _effectSerializer;

};

}

#endif // PICKABLE_SERIALIZER_H
