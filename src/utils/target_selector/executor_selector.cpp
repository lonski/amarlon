#include "executor_selector.h"
#include "actor/actor.h"

namespace amarlon {

ExecutorSelector::ExecutorSelector()
{
}

std::vector<ActorPtr > ExecutorSelector::select(std::function<bool (amarlon::ActorPtr)>*)
{
  std::vector<ActorPtr> targets;
  targets.push_back( Actor::Player );

  return targets;
}

}
