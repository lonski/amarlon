#include "Ai.h"
#include "Actor/Actor.h"
#include <iostream>
#include "MonsterAi.h"

namespace amarlon {

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

Ai *Ai::create(const AiDescription &dsc)
{
  return Ai::create(dsc.type);
}

void Ai::update(Map*)
{
  if (_owner)
  {
    std::cout << "\n" << _owner->getName() << " updates";
  }
}

}
