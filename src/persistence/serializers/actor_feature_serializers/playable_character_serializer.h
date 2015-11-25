#ifndef PLAYABLE_CHARACTER_SERIALIZER_H
#define PLAYABLE_CHARACTER_SERIALIZER_H

#include <memory>
#include <character_serializer.h>

namespace amarlon {

class PlayableCharacterSerializer : public CharacterSerializer
{
public:
  PlayableCharacterSerializer();
  PlayableCharacterSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~PlayableCharacterSerializer();

  virtual bool serialize(ActorFeaturePtr af);

};

}

#endif // PLAYABLE_CHARACTER_SERIALIZER_H
