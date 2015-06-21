#ifndef MONSTER_SERIALIZER_H
#define MONSTER_SERIALIZER_H

#include <memory>
#include <character_serializer.h>

namespace amarlon {

class MonsterSerializer : public CharacterSerializer
{
public:
  MonsterSerializer();
  MonsterSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~MonsterSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // MONSTER_SERIALIZER_H
