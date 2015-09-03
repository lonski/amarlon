#ifndef SPELL_SERIALIZER_H
#define SPELL_SERIALIZER_H

#include <memory>
#include <serializer.h>
#include <effect_serializer.h>

namespace amarlon {

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class SpellSerializer : public Serializer
{
public:
  SpellSerializer();
  SpellSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~SpellSerializer();

  virtual bool serialize(SpellPtr spell);

private:
  EffectSerializer _effectSerializer;

};

}
#endif // SPELL_SERIALIZER_H
