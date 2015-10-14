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
    , symbol('X')
    , color(TCODColor::white)
    , blocks(false)
    , fovOnly(false)
    , transparent(false)
    , tilePriority(666)
  {}

  ActorType id;
  std::string name;
  unsigned char symbol;
  TCODColor color;
  bool blocks;
  bool fovOnly;
  bool transparent;  
  int tilePriority;
  std::string description;
  std::vector<StatusEffectDsc> statusEffects;

  PickableDescriptionPtr pickable;
  CharacterDescriptionPtr character;
  AiDescriptionPtr ai;
  OpenableDescriptionPtr openable;
  WearerDescriptionPtr wearer;
  InventoryDescriptionPtr inventory;
  DestroyableDescriptionPtr destroyable;
};

typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;

}

#endif // ACTORDESCRIPTIONS_H
