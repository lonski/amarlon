#include "ai.h"
#include <iostream>
#include <ai_factory.h>
#include <actor_descriptions.h>

namespace amarlon {

const ActorFeature::Type Ai::featureType = ActorFeature::AI;

Ai::Ai()
{
}

AiPtr Ai::create(DescriptionPtr dsc)
{
  static AiFactory factory;
  return factory.produce( std::dynamic_pointer_cast<AiDescription>(dsc) );
}

}

