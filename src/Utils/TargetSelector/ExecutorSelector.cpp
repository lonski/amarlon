#include "ExecutorSelector.h"

namespace amarlon {

ExecutorSelector::ExecutorSelector()
{
}

std::vector<Actor *> ExecutorSelector::select(Actor *executor, Map*, bool(*)(Actor *))
{
  std::vector<Actor*> targets;
  targets.push_back(executor);

  return targets;
}

}
