#include "executor_selector.h"
#include "actor/actor.h"

namespace amarlon {

ExecutorSelector::ExecutorSelector()
{
}

std::vector<Actor *> ExecutorSelector::select(bool(*)(Actor *))
{
  std::vector<Actor*> targets;
  targets.push_back( Actor::Player );

  return targets;
}

}
