#ifndef CHARACTER_CLASS_DESCRIPTION
#define CHARACTER_CLASS_DESCRIPTION

#include <description.h>
#include <item_type_description.h>
#include <vector>

namespace amarlon {

struct CharacterClassDescription : Description
{
  int id;
  std::string name;
  std::string description;
  bool playable;
  std::vector< std::pair<int, MinMax> > abilityScoreRestrictions;
  std::vector< ItemTypeDescription > itemTypeRestrictions;
};

typedef std::shared_ptr<CharacterClassDescription> CharacterClassDescriptionPtr;

}

#endif // CHARACTER_CLASS_DESCRIPTION

