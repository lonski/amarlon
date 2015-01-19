#ifndef ACTORDESCRIPTIONS_H
#define ACTORDESCRIPTIONS_H

#include <memory>
#include <cstring>
#include <string>
#include <vector>
#include <libtcod.hpp>
#include "actor/actor_type.h"
#include "actor/actor_features/ai/ai_type.h"
#include "actor/actor_features/openable/openable_type.h"
#include "actor/actor_features/wearer/item_slot_type.h"
#include "actor/actor_features/pickable_category.h"
#include "actor/effects/effect_type.h"

namespace amarlon {

class Container;
class Pickable;
class Fighter;
class Ai;
class Openable;
class Wearer;

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

//===
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

struct WearerDescription;

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
  std::vector<ItemSlotType> itemSlots;
  ContainerDescription eqItems;
};

//===
}

#endif // ACTORDESCRIPTIONS_H
