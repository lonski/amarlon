#include "ai.h"
#include "Actor/Actor.h"
#include "monster_ai.h"
#include <amarlon_except.h>
#include <iostream>

namespace amarlon {

const ActorFeature::Type Ai::featureType = ActorFeature::AI;

Ai::Ai()
{
}

Ai *Ai::create(AiType type)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  Ai* ai = nullptr;

  switch (type)
  {
    case AiType::Monster: ai = new MonsterAi;
    default:;
  }

  return ai;
}

Ai *Ai::create(Description* dsc)
{
  AiDescription* aiDsc = dynamic_cast<AiDescription*>(dsc);
  Ai* ai = nullptr;

  if ( aiDsc != nullptr )
  {
    ai = Ai::create(aiDsc->type);
  }else throw creation_error("Wrong ai description!");

  return ai;
}

void Ai::update(Map*)
{
  if (_owner)
  {
    std::cout << "\n" << _owner->getName() << " updates";
  }
}

}
