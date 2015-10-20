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
      performer->setVisible(true);
      if ( openable->open(performer) )
      {
        MapPtr map = _toOpen->getMap();
        if ( map )
        {
          map->updateTile( _toOpen->getX(), _toOpen->getY() );
        }
        opened = true;
      }
    }
  }

  return opened;
}

ActorActionUPtr OpenAction::clone()
{
  OpenActionUPtr cloned = std::make_unique<OpenAction>(_toOpen);
  return std::move(cloned);
}

}

