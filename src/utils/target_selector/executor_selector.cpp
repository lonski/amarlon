#include "executor_selector.h"
#include "actor/actor.h"

namespace amarlon {

ExecutorSelector::ExecutorSelector()
{
}

Target ExecutorSelector::select(std::function<bool (amarlon::ActorPtr)>*)
{
  return Target( std::vector<ActorPtr>{ Actor::Player }, Actor::Player->getX(), Actor::Player->getY() );
}

}
