#ifndef CHARACTER_SERIALIZER_H
#define CHARACTER_SERIALIZER_H

#include <memory>
#include <actor_feature_serializer.h>

namespace amarlon {

class Character;
typedef std::shared_ptr<Character> CharacterPtr;

class CharacterSerializer : public ActorFeatureSerializer
{
public:
  CharacterSerializer();
  CharacterSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~CharacterSerializer();

  virtual bool serialize(ActorFeaturePtr af);
  
protected:
  void serializeCharacterCommonPart(rapidxml::xml_node<>* characterNode, CharacterPtr character);
  void serializeSpellbook(rapidxml::xml_node<>* characterNode, CharacterPtr character);
  void serializeSkills(CharacterPtr character, rapidxml::xml_node<>* characterNode);
  void serializeModifiers(CharacterPtr character, rapidxml::xml_node<>* characterNode);
  void serializeAbilityScores(CharacterPtr character, rapidxml::xml_node<>* characterNode);

};

}

#endif // CHARACTER_SERIALIZER_H
