#include "ActorFeature.h"

ActorFeature::ActorFeature()
  : _owner(nullptr)
{
}

ActorFeature::~ActorFeature()
{
}

void ActorFeature::setOwner(Actor *owner)
{
  _owner = owner;
}
