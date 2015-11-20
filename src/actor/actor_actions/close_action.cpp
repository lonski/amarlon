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

ActorActionResult CloseAction::perform(ActorPtr performer)
{
  ActorActionResult r = ActorActionResult::Nok;

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
          map->updateTile( _toClose->getX(), _toClose->getY() );
        }
        r = ActorActionResult::Ok;
      }
    }
  }

  return r;
}

ActorActionUPtr CloseAction::clone()
{
  CloseActionUPtr cloned = std::make_unique<CloseAction>(_toClose);
  return std::move(cloned);
}

}

