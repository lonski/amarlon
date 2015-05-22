#ifndef ACTORDESCRIPTIONS_H
#define ACTORDESCRIPTIONS_H

#include <memory>
#include <cstring>
#include <string>
#include <vector>
#include <libtcod.hpp>
#include <actor_type.h>
#include <ai_type.h>
#include <openable_type.h>
#include <item_slot_type.h>
#include <pickable_category.h>
#include <effect_type.h>
#include <drop_rule.h>

namespace amarlon {

class Container;
class Pickable;
class Fighter;
class Ai;
class Openable;
class Wearer;
class Destroyable;

struct Description;
struct ActorDescription;
struct PickableDescription;
struct FighterDescription;
struct AiDescription;
struct OpenableDescription;
struct WearerDescription;
struct ContainerDescription;
struct DestroyableDescription;

typedef std::shared_ptr<Description> DescriptionPtr;
typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;
typedef std::shared_ptr<PickableDescription> PickableDescriptionPtr;
typedef std::shared_ptr<FighterDescription> FighterDescriptionPtr;
typedef std::shared_ptr<AiDescription> AiDescriptionPtr;
typedef std::shared_ptr<OpenableDescription> OpenableDescriptionPtr;
typedef std::shared_ptr<WearerDescription> WearerDescriptionPtr;
typedef std::shared_ptr<ContainerDescription> ContainerDescriptionPtr;
typedef std::shared_ptr<DestroyableDescription> DestroyableDescriptionPtr;

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
  ActorType id;
  std::string name;
  unsigned char character;
  TCODColor color;
  bool blocks;
  bool fovOnly;
  bool transparent;  
  int tilePriority;
};

struct PickableDescription : Description
{
  bool stackable;
  int amount;
  EffectDescription effect;
  ItemSlotType itemSlot;
  PickableCategory category;
};

struct FighterDescription : Description
{
  float maxHp;
  float power;
};

struct AiDescription : Description
{
  AiType type;
};

struct OpenableDescription : Description
{
  OpenableType type;
  int lockId;
  bool locked;
};

struct ContainerDescription : Description
{
  ContainerDescription() : maxSize(0) {}

  struct Content
  {
    ActorType actorType;
    std::shared_ptr<ContainerDescription> container;
    std::shared_ptr<PickableDescription> pickable;
    std::shared_ptr<FighterDescription> fighter;
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
