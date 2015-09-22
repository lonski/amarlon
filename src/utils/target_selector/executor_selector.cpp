#include "executor_selector.h"
#include <actor.h>
#include <engine.h>

namespace amarlon {

ExecutorSelector::ExecutorSelector()
{
}

Target ExecutorSelector::select(std::function<bool (amarlon::ActorPtr)>)
{
  return Target( std::vector<ActorPtr>{ Engine::instance().getPlayer() }, Engine::instance().getPlayer()->getX(), Engine::instance().getPlayer()->getY() );
}

}

