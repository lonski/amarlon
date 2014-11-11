#ifndef ACTORDESCRIPTIONS_H
#define ACTORDESCRIPTIONS_H

#include <memory>
#include <cstring>
#include <string>
#include <vector>
#include <libtcod.hpp>
#include "Actor/ActorType.h"
#include "Actor/ActorFeatures/Ai/AiType.h"
#include "Actor/ActorFeatures/Openable/OpenableType.h"
#include "Actor/Effects/EffectType.h"
#include "Actor/ActorFeatures/Wearer/item_slot_type.h"
#include <Actor/ActorFeatures/pickable_category.h>

namespace amarlon {

class Container;
class Pickable;
class Fighter;
class Ai;
class Openable;
class Wearer;

struct EffectDescription
{
  EffectDescription() { memset(this, 0, sizeof *this); }

  EffectType type;
  int lockId;
  int uses;
  int heal;
};

//===
struct ActorDescription
{
  ActorType id;
  std::string name;
  unsigned char character;
  TCODColor color;
  bool blocks;
  bool fovOnly;
  bool transparent;  
};

struct PickableDescription
{
  bool stackable;
  int amount;
  EffectDescription effect;
  ItemSlotType itemSlot;
  PickableCategory category;
};

struct FighterDescription
{
  float maxHp;
  float power;
};

struct AiDescription
{
  AiType type;
};

struct OpenableDescription
{
  OpenableType type;
  int lockId;
  bool locked;
};

struct WearerDescription;

struct ContainerDescription
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
    {
    }
  };

  size_t maxSize;
  std::vector<Content> content;
};

struct WearerDescription
{
  std::vector<ItemSlotType> itemSlots;
  ContainerDescription eqItems;
};

//===
}

#endif // ACTORDESCRIPTIONS_H
