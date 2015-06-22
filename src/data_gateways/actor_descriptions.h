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
#include <effect_type.h>
#include <drop_rule.h>
#include <dices.h>
#include <character_classes.h>
#include <ability_scores.h>
#include <races.h>

namespace amarlon {

class Container;
class Pickable;
class Character;
class Ai;
class Openable;
class Wearer;
class Destroyable;

struct Description;
struct ActorDescription;
struct PickableDescription;
struct PlayableCharacterDescription;
struct AiDescription;
struct MonsterAiDescription;
struct OpenableDescription;
struct OpenableContainerDescription;
struct OpenableDoorDescription;
struct WearerDescription;
struct ContainerDescription;
struct DestroyableDescription;
struct MonsterDescription;
struct CharacterDescription;

typedef std::shared_ptr<Description> DescriptionPtr;
typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;
typedef std::shared_ptr<PickableDescription> PickableDescriptionPtr;
typedef std::shared_ptr<PlayableCharacterDescription> PlayableCharacterDescriptionPtr;
typedef std::shared_ptr<AiDescription> AiDescriptionPtr;
typedef std::shared_ptr<MonsterAiDescription> MonsterAiDescriptionPtr;
typedef std::shared_ptr<OpenableDescription> OpenableDescriptionPtr;
typedef std::shared_ptr<OpenableContainerDescription> OpenableContainerDescriptionPtr;
typedef std::shared_ptr<OpenableDoorDescription> OpenableDoorDescriptionPtr;
typedef std::shared_ptr<WearerDescription> WearerDescriptionPtr;
typedef std::shared_ptr<ContainerDescription> ContainerDescriptionPtr;
typedef std::shared_ptr<DestroyableDescription> DestroyableDescriptionPtr;
typedef std::shared_ptr<MonsterDescription> MonsterDescriptionPtr;
typedef std::shared_ptr<CharacterDescription> CharacterDescriptionPtr;

struct Description
{
  virtual ~Description() {}
};

struct EffectDescription : Description
{
  EffectDescription()
    : type(EffectType::Null)
    , lockId(0)
    , uses(0)
    , heal(0)
  {
  }

  EffectType type;
  int lockId;
  int uses;
  int heal;
};

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
    , itemSlot(ItemSlotType::Null)
    , category(PickableCategory::Miscellaneous)
    , damageDice(dices::NoDice)
    , armorClass(0)
    , weight(0)
    , price(0)
    , damageDiceCount(0)
  {}

  bool stackable;
  int amount;

  EffectDescription effect;
  ItemSlotType itemSlot;
  PickableCategory category;
  dices::Dice damageDice;
  int armorClass;
  int weight;
  int price;
  int damageDiceCount;
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
};

struct PlayableCharacterDescription : CharacterDescription
{  
  std::map<AbilityScore::Type, int> abilityScores;  
};

struct MonsterDescription : CharacterDescription
{
  MonsterDescription()
    : hitPointsBonus(0)
    , damageDice(dices::NoDice)
    , damageDiceCount(0)
    , morale(0)
  {}

  int hitPointsBonus;
  dices::Dice damageDice;
  int damageDiceCount;
  int morale;  
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

struct OpenableContainerDescription : OpenableDescription
{
};

struct ContainerDescription : Description
{
  ContainerDescription() : maxSize(0) {}

  struct Content
  {
    ActorType actorType;
    std::shared_ptr<ContainerDescription> container;
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
    eqItems( new ContainerDescription )
  {}

  std::vector<ItemSlotType> itemSlots;
  std::shared_ptr<ContainerDescription> eqItems;
};

struct DestroyableDescription : Description
{
  DestroyableDescription()
  {}

  std::vector<DropRule> dropRules;
};

}

#endif // ACTORDESCRIPTIONS_H
