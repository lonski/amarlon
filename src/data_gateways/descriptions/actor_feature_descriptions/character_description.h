#ifndef CHARACTER_DESCRIPTION
#define CHARACTER_DESCRIPTION

#include <vector>
#include <character_class_type.h>
#include <race_type.h>
#include <ability_scores.h>
#include <damage.h>
#include <description.h>
#include <character_type.h>
#include <relations.h>
#include <experimental/optional>

namespace amarlon {

struct SkillDescription
{
  SkillDescription(int id = 0, int level = 0)
    : id(id)
    , level(level)
  {}
  int id;
  int level;
};

struct SpellSlotDescription
{
  int level;
  int spell;
  bool prepared;
};

struct SpellbookDescription
{
  std::vector<SpellSlotDescription> spellSlots;
  std::vector<int> knownSpells;
};

struct CharacterDescription : Description
{
  std::experimental::optional<int> level;
  std::experimental::optional<int> hitPoints;
  std::experimental::optional<int> maxHitPoints;
  std::experimental::optional<int> defaultArmorClass;
  std::experimental::optional<int> experience;
  std::experimental::optional<CharacterClassType> cClass;
  std::experimental::optional<RaceType> race;
  std::experimental::optional<int> speed;
  std::experimental::optional<CharacterType> type;
  std::experimental::optional<relations::Team> team;
  std::experimental::optional<int> morale;
  std::experimental::optional<Damage> damage;
  std::experimental::optional<SpellbookDescription> spellbook;

  std::vector<SkillDescription> skills;
  std::vector<std::string> modifiers;
  std::map<AbilityScore::Type, int> abilityScores;
};


struct PlayableCharacterDescription : CharacterDescription
{
};

typedef std::shared_ptr<SpellbookDescription> SpellbookDescriptionPtr;
typedef std::shared_ptr<CharacterDescription> CharacterDescriptionPtr;
typedef std::shared_ptr<PlayableCharacterDescription> PlayableCharacterDescriptionPtr;

}

#endif // CHARACTER_DESCRIPTION

