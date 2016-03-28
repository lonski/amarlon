#include "open_action.h"
#include <actor.h>
#include <map.h>

namespace amarlon{

OpenAction::OpenAction(ActorPtr toOpen)
  : _toOpen(toOpen)
{
}

OpenAction::~OpenAction()
{
}

ActorActionResult OpenAction::perform(ActorPtr performer)
{
  ActorActionResult r = ActorActionResult::Nok;

  if ( _toOpen )
  {
    OpenablePtr openable = _toOpen->getFeature<Openable>();
    if ( openable )
    {
      if ( openable->open(performer) )
      {
        MapPtr map = _toOpen->getMap();
        if ( map )
        {
          map->updateTile( _toOpen->getX(), _toOpen->getY() );
        }
        r = ActorActionResult::Ok;
      }
    }
  }

  return r;
}

ActorActionUPtr OpenAction::clone()
{
  OpenActionUPtr cloned = std::make_unique<OpenAction>(_toOpen);
  return std::move(cloned);
}

}

