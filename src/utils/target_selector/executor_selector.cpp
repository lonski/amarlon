#include "executor_selector.h"
#include <actor.h>
#include <engine.h>
#include <map.h>

namespace amarlon {

ExecutorSelector::ExecutorSelector()
{
}

Target ExecutorSelector::select(std::function<bool (amarlon::ActorPtr)>)
{
  return Target( std::vector<ActorPtr>{ Engine::instance().getPlayer() }, Engine::instance().getPlayer()->getX(), Engine::instance().getPlayer()->getY() );
}

ExecutorAreaSelector::ExecutorAreaSelector()
{
}

Target ExecutorAreaSelector::select(std::function<bool (ActorPtr)> filterFun)
{
  ActorPtr player = Engine::instance().getPlayer();
  MapPtr map = player->getMap();
  if ( map )
  {
    std::function<bool(ActorPtr)> filter = [&](ActorPtr a){ return map->isInFov(a->getX(), a->getY()) && filterFun(a); };
    return Target( map->getActors(player->getX(), player->getY(), getRadius(), filter), player->getX(), player->getY() );
  }
  return Target();
}

}

