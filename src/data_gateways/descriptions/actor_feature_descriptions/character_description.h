#ifndef CHARACTER_DESCRIPTION
#define CHARACTER_DESCRIPTION

#include <vector>
#include <character_class_type.h>
#include <race_type.h>
#include <ability_scores.h>
#include <damage.h>
#include <description.h>

namespace amarlon {

struct SkillDescription
{
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
  CharacterDescription()
    : level(0)
    , hitPoints(0)
    , maxHitPoints(0)
    , defaultArmorClass(0)
    , experience(0)
    , cClass(CharacterClassType::Fighter)
    , race(RaceType::NoRace)
    , speed(0)
  {}

  int level;
  int hitPoints;
  int maxHitPoints;
  int defaultArmorClass;
  int experience;
  CharacterClassType cClass;
  RaceType race;
  int speed;
  SpellbookDescription spellbook;
  std::vector<SkillDescription> skills;
};


struct PlayableCharacterDescription : CharacterDescription
{
  std::map<AbilityScore::Type, int> abilityScores;
};

struct MonsterDescription : CharacterDescription
{
  MonsterDescription()
    : hitPointsBonus(0)
    , morale(0)
  {}

  int hitPointsBonus;
  int morale;
  Damage damage;
};

typedef std::shared_ptr<SpellbookDescription> SpellbookDescriptionPtr;
typedef std::shared_ptr<MonsterDescription> MonsterDescriptionPtr;
typedef std::shared_ptr<CharacterDescription> CharacterDescriptionPtr;
typedef std::shared_ptr<PlayableCharacterDescription> PlayableCharacterDescriptionPtr;

}

#endif // CHARACTER_DESCRIPTION

