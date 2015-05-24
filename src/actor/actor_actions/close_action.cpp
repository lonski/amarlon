#include "close_action.h"

#include <actor.h>
#include <map.h>

namespace amarlon {

CloseAction::CloseAction(ActorPtr toClose)
  : _toClose(toClose)
{
}

CloseAction::~CloseAction()
{
}

bool CloseAction::perform(ActorPtr performer)
{
  bool closed = false;

  if ( _toClose )
  {
    OpenablePtr openable = _toClose->getFeature<Openable>();
    if ( openable )
    {
      if ( openable->close(performer) )
      {
        MapPtr map = _toClose->getMap();
        if ( map )
        {
          map->updateActorCell(_toClose);
        }
        closed = true;
      }
    }
  }

  return closed;
}

ActorActionUPtr CloseAction::clone()
{
  CloseActionUPtr cloned = std::make_unique<CloseAction>(_toClose);
  return std::move(cloned);
}

}
