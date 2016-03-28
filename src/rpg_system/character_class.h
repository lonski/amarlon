#ifndef CHARACTER_CLASS_H
#define CHARACTER_CLASS_H

#include <memory>
#include <character_class_type.h>
#include <ability_scores.h>
#include <utils.h>
#include <item_type.h>

namespace amarlon {

class CharacterClass;
struct CharacterClassDescription;
typedef std::shared_ptr<CharacterClass> CharacterClassPtr;
typedef std::shared_ptr<CharacterClassDescription> CharacterClassDescriptionPtr;

class CharacterClass
{
public:
  CharacterClass();
  static CharacterClassPtr create(CharacterClassType type);
  static CharacterClassPtr create(CharacterClassDescriptionPtr dsc);
  CharacterClassPtr clone() const;
  bool operator==(const CharacterClass& rhs) const;

  CharacterClassType getType() const;
  std::string getName() const;
  std::string getDescription() const;
  bool isPlayable() const;

  const std::vector<ItemTypeRestriction> getItemRestrictions() const;
  bool isItemAllowed(ItemType itemType);
  MinMax getAbilityScoreRestriction(AbilityScore::Type as) const;

private:
  CharacterClassType _id;
  std::string _name;
  std::string _description;
  bool _playable;

  std::map<AbilityScore::Type, MinMax> _abilityScoreRestrictions;
  std::vector<ItemTypeRestriction> _itemTypeRestrictions;

  friend class RpgParser;

};

}

#endif // CHARACTER_CLASS_H
