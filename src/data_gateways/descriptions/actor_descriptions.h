#ifndef ACTORDESCRIPTIONS_H
#define ACTORDESCRIPTIONS_H

#include <description.h>
#include <pickable_description.h>
#include <character_description.h>
#include <ai_description.h>
#include <openable_description.h>
#include <wearer_description.h>
#include <inventory_description.h>
#include <destroyable_description.h>
#include <trap_description.h>

#include <experimental/optional>

namespace amarlon {

struct StatusEffectDsc
{
  int spellId;
  int duration;
};

struct ActorDescription : Description
{
  ActorDescription()
    : id(ActorType::Null)
  {}

  ActorType id;
  std::experimental::optional<int> x;
  std::experimental::optional<int> y;
  std::experimental::optional<std::string> name;
  std::experimental::optional<unsigned char> symbol;
  std::experimental::optional<TCODColor> color;
  std::experimental::optional<bool> blocks;
  std::experimental::optional<bool> fovOnly;
  std::experimental::optional<bool> transparent;
  std::experimental::optional<int> tilePriority;
  std::experimental::optional<std::string> description;
  std::vector<StatusEffectDsc> statusEffects;

  PickableDescriptionPtr pickable;
  CharacterDescriptionPtr character;
  AiDescriptionPtr ai;
  OpenableDescriptionPtr openable;
  WearerDescriptionPtr wearer;
  InventoryDescriptionPtr inventory;
  DestroyableDescriptionPtr destroyable;
  TrapDescriptionPtr trap;

};

typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;

}

#endif // ACTORDESCRIPTIONS_H
