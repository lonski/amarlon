#include "Ai.h"
#include "Actor/Actor.h"
#include <iostream>
#include "MonsterAi.h"

Ai::Ai()
{
}

Ai *Ai::create(AiType type)
{
  Ai* ai = nullptr;

  switch (type)
  {
    case AiType::Monster: ai = new MonsterAi;
    default:;
  }

  return ai;
}

void Ai::update(Map*)
{
  if (_owner)
  {
    std::cout << "\n" << _owner->getName() << " updates";
  }
}
