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

bool OpenAction::perform(ActorPtr performer)
{
  bool opened = false;

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
          map->updateActorCell(_toOpen);
        }
        opened = true;
      }
    }
  }

  return opened;
}

}
