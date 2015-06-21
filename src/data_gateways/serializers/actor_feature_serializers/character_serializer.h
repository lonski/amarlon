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

  /** Character is an abstract class - here is just common serialization in protected section
   *  which should be called in each serializer for given Character type
   */
  virtual bool serialize(ActorFeaturePtr af) = 0;

protected:
  void serializeCharacterCommonPart(rapidxml::xml_node<>* characterNode, CharacterPtr character);

};

}

#endif // CHARACTER_SERIALIZER_H
