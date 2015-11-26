#ifndef CHARACTER_DESCRIPTION
#define CHARACTER_DESCRIPTION

#include <map>
#include <vector>
#include <description.h>
#include <experimental/optional>
#include <spellbook_description.h>

namespace amarlon {

struct SkillDescription : Description
{
  SkillDescription(int id = 0, int level = 0)
    : id(id)
    , level(level)
  {}
  int id;
  int level;
};

struct CharacterDescription : Description
{
  std::experimental::optional<int> level;
  std::experimental::optional<int> hitPoints;
  std::experimental::optional<int> maxHitPoints;
  std::experimental::optional<int> defaultArmorClass;
  std::experimental::optional<int> experience;
  std::experimental::optional<int> cClass;
  std::experimental::optional<int> race;
  std::experimental::optional<int> speed;
  std::experimental::optional<int> type;
  std::experimental::optional<int> team;
  std::experimental::optional<int> morale;
  std::experimental::optional<std::string> damage;
  std::experimental::optional<SpellbookDescription> spellbook;

  std::vector<SkillDescription> skills;
  std::vector<std::string> modifiers;
  std::map<int, int> abilityScores;
};

typedef std::shared_ptr<SpellbookDescription> SpellbookDescriptionPtr;
typedef std::shared_ptr<CharacterDescription> CharacterDescriptionPtr;

}

#endif // CHARACTER_DESCRIPTION

