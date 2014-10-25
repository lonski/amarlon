#include "ActorFeature.h"

namespace amarlon {

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

}
