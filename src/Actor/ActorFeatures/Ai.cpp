#include "Ai.h"
#include "Actor/Actor.h"
#include <iostream>
#include "MonsterAi.h"

Ai::Ai()
  : _owner(nullptr)
{
}

Ai *Ai::create(AiType type)
{
  Ai* ai = nullptr;

  switch (type)
  {
    case AiType::Monster: ai = new MonsterAi;
  }

  return ai;
}

void Ai::setOwner(Actor *owner)
{
  _owner = owner;
}

void Ai::update(Map *map)
{
  if (_owner)
  {
    std::cout << "\n" << _owner->getName() << " updates";
  }
}
