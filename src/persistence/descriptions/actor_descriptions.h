#ifndef ACTORDESCRIPTIONS_H
#define ACTORDESCRIPTIONS_H

#include <map>
#include <experimental/optional>

#include <description.h>

#include <pickable_description.h>
#include <character_description.h>
#include <ai_description.h>
#include <openable_description.h>
#include <wearer_description.h>
#include <inventory_description.h>
#include <destroyable_description.h>
#include <trap_description.h>
#include <talker_description.h>

namespace amarlon {

struct StatusEffectDsc
{
  std::string name;
  std::string script;
  int duration;
};

struct ActorDescription : Description
{
  std::experimental::optional<int> id;
  std::experimental::optional<int> prototype;
  std::experimental::optional<int> x;
  std::experimental::optional<int> y;
  std::experimental::optional<std::string> name;
  std::experimental::optional<unsigned char> symbol;
  std::experimental::optional<std::string> color;
  std::experimental::optional<bool> blocks;
  std::experimental::optional<bool> fovOnly;
  std::experimental::optional<bool> transparent;
  std::experimental::optional<bool> visible;
  std::experimental::optional<int> tilePriority;
  std::experimental::optional<std::string> description;
  std::vector<StatusEffectDsc> statusEffects;

  std::map<int, DescriptionPtr> features;

};

typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;

}

#endif // ACTORDESCRIPTIONS_H
