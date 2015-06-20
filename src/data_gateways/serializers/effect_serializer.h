#ifndef EFFECT_SERIALIZER_H
#define EFFECT_SERIALIZER_H

#include <memory>
#include <serializer.h>

namespace amarlon {

class Effect;
typedef std::shared_ptr<Effect> EffectPtr;

class EffectSerializer : public Serializer
{
public:
  EffectSerializer();
  EffectSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~EffectSerializer();

  virtual bool serialize(Effect* effect);

};

}

#endif // EFFECT_SERIALIZER_H
