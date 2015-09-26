#ifndef ACTORDESCRIPTIONS_H
#define ACTORDESCRIPTIONS_H

#include <memory>
#include <cstring>
#include <string>
#include <vector>
#include <map>
#include <libtcod.hpp>
#include <actor_type.h>
#include <item_slot_type.h>
#include <pickable_category.h>
#include <drop_rule.h>
#include <dices.h>
#include <character_classes.h>
#include <ability_scores.h>
#include <races.h>
#include <target_type.h>
#include <description.h>
#include <spell_id.h>
#include <set>
#include <damage.h>

namespace amarlon {

class Inventory;
class Pickable;
class Character;
class Ai;
class Openable;
class Wearer;
class Destroyable;

struct ActorDescription;
struct PickableDescription;
struct PlayableCharacterDescription;
struct AiDescription;
struct MonsterAiDescription;
struct OpenableDescription;
struct OpenableContaineryDescription;
struct OpenableDoorDescription;
struct WearerDescription;
struct InventoryDescription;
struct DestroyableDescription;
struct MonsterDescription;
struct CharacterDescription;

typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;
typedef std::shared_ptr<PickableDescription> PickableDescriptionPtr;
typedef std::shared_ptr<PlayableCharacterDescription> PlayableCharacterDescriptionPtr;
typedef std::shared_ptr<AiDescription> AiDescriptionPtr;
typedef std::shared_ptr<MonsterAiDescription> MonsterAiDescriptionPtr;
typedef std::shared_ptr<OpenableDescription> OpenableDescriptionPtr;
typedef std::shared_ptr<OpenableContaineryDescription> OpenableContaineryDescriptionPtr;
typedef std::shared_ptr<OpenableDoorDescription> OpenableDoorDescriptionPtr;
typedef std::shared_ptr<WearerDescription> WearerDescriptionPtr;
typedef std::shared_ptr<InventoryDescription> InventoryDescriptionPtr;
typedef std::shared_ptr<DestroyableDescription> DestroyableDescriptionPtr;
typedef std::shared_ptr<MonsterDescription> MonsterDescriptionPtr;
typedef std::shared_ptr<CharacterDescription> CharacterDescriptionPtr;

struct ActorDescription : Description
{
  ActorDescription()
    : id(ActorType::Null)
    , character('X')
    , color(TCODColor::white)
    , blocks(false)
    , fovOnly(false)
    , transparent(false)
    , tilePriority(666)
  {}

  ActorType id;
  std::string name;
  unsigned char character;
  TCODColor color;
  bool blocks;
  bool fovOnly;
  bool transparent;  
  int tilePriority;
  std::string description;
};

struct PickableDescription : Description
{
  PickableDescription()
    : stackable(false)
    , amount(1)
    , uses(0)
    , itemSlot(ItemSlotType::Null)
    , category(PickableCategory::Miscellaneous)
    , armorClass(0)
    , weight(0)
    , price(0)
    , targetType(TargetType::SINGLE_NEIGHBOUR)
  {}

  bool stackable;
  int amount;
  int uses;

  ItemSlotType itemSlot;
  PickableCategory category;
  int armorClass;
  int weight;
  int price;
  TargetType targetType;
  Damage damage;
};


struct CharacterDescription : Description
{
  CharacterDescription()
    : level(0)
    , hitPoints(0)
    , maxHitPoints(0)
    , defaultArmorClass(0)
    , experience(0)
    , cClass(CharacterClass::Fighter)
    , race(Race::NoRace)
    , speed(0)
  {}

  int level;
  int hitPoints;
  int maxHitPoints;
  int defaultArmorClass;
  int experience;
  CharacterClass cClass;
  Race race;
  int speed;
  std::set<SpellId> spells;
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

struct AiDescription : Description
{
};

struct MonsterAiDescription : AiDescription
{
};

struct OpenableDescription : Description
{
  OpenableDescription()
    : lockId(0)
    , locked(false)
  {}

  int lockId;
  bool locked;
};

struct OpenableDoorDescription : OpenableDescription
{
};

struct OpenableContaineryDescription : OpenableDescription
{
};

struct InventoryDescription : Description
{
  InventoryDescription() : maxSize(0) {}

  struct Content
  {
    ActorType actorType;
    std::shared_ptr<InventoryDescription> container;
    std::shared_ptr<PickableDescription> pickable;
    std::shared_ptr<Description> character;
    std::shared_ptr<AiDescription> ai;
    std::shared_ptr<OpenableDescription> openable;
    std::shared_ptr<WearerDescription> wearer;
    std::shared_ptr<DestroyableDescription> destroyable;

    Content()
      : actorType(ActorType::Null)
    {
    }
  };

  size_t maxSize;
  std::vector<Content> content;
};

struct WearerDescription : Description
{
  WearerDescription()
    :
    eqItems( new InventoryDescription )
  {}

  std::vector<ItemSlotType> itemSlots;
  std::shared_ptr<InventoryDescription> eqItems;
};

struct DestroyableDescription : Description
{
  DestroyableDescription()
  {}

  std::vector<DropRule> dropRules;
};

}

#endif // ACTORDESCRIPTIONS_H
