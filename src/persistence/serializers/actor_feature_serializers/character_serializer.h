#ifndef CHARACTER_SERIALIZER_H
#define CHARACTER_SERIALIZER_H

#include <memory>
#include <serializer.h>

namespace amarlon {

struct CharacterDescription;
typedef std::shared_ptr<CharacterDescription> CharacterDescriptionPtr;

class CharacterSerializer : public Serializer
{
public:
  CharacterSerializer();
  CharacterSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~CharacterSerializer();

  virtual bool serialize(DescriptionPtr dsc);
  
protected:
  void serializeSpellbook(CharacterDescriptionPtr dsc, rapidxml::xml_node<>* characterNode);
  void serializeSkills(CharacterDescriptionPtr dsc, rapidxml::xml_node<>* characterNode);
  void serializeModifiers(CharacterDescriptionPtr dsc, rapidxml::xml_node<>* characterNode);
  void serializeAbilityScores(CharacterDescriptionPtr dsc, rapidxml::xml_node<>* characterNode);

};

}

#endif // CHARACTER_SERIALIZER_H
