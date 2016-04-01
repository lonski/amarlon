#include "actor_feature.h"
#include <ai.h>
#include <openable.h>
#include <wearer.h>
#include <character.h>
#include <pickable.h>
#include <destroyable.h>
#include <inventory.h>
#include <trap.h>
#include <actor.h>
#include <talker.h>

namespace amarlon {

ActorFeature::ActorFeature()
{
}

ActorFeature::~ActorFeature()
{
}

void ActorFeature::setOwner(ActorWPtr owner)
{
  _owner = owner;
}

ActorWPtr ActorFeature::getOwner() const
{
  return _owner;
}

std::string ActorFeature::getDescription()
{
  return "";
}

std::string ActorFeature::debug(const std::string &)
{
  return "";
}

int ActorFeature::update()
{
  return 0;
}

}

