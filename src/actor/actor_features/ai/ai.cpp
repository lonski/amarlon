#include "ai.h"
#include <iostream>
#include "actor/actor.h"
#include "monster_ai.h"
#include "amarlon_except.h"

namespace amarlon {

const ActorFeature::Type Ai::featureType = ActorFeature::AI;

Ai::Ai()
{
}

AiPtr Ai::create(AiType type)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  AiPtr ai;

  switch (type)
  {
    case AiType::Monster: ai.reset( new MonsterAi );
    default:;
  }

  return ai;
}

AiPtr Ai::create(DescriptionPtr dsc)
{
  AiDescriptionPtr aiDsc = std::dynamic_pointer_cast<AiDescription>(dsc);
  AiPtr ai = nullptr;

  if ( aiDsc != nullptr )
  {
    ai = Ai::create(aiDsc->type);
  }else throw creation_error("Wrong ai description!");

  return ai;
}

}
