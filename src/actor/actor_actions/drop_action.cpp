#include "drop_action.h"
#include <actor.h>
#include <map.h>
#include <messenger.h>

namespace amarlon {

DropAction::DropAction(ActorPtr toDrop, int amount)
  : _toDrop(toDrop)
  , _amount(amount)
{
}

DropAction::~DropAction()
{
}

bool DropAction::perform(ActorPtr performer)
{
  bool dropped = false;

  if ( _toDrop )
  {
    _performer = performer;
    PickablePtr pickable = _toDrop->getFeature<Pickable>();

    if ( pickable->isStackable() && _amount < pickable->getAmount() )
    {
      dropOnMap( pickable->spilt(_amount) );
      dropped = true;
    }
    else
    {
      dropOnMap(_toDrop);
      _performer->getFeature<Container>()->remove(_toDrop);
      dropped = true;
    }
  }

  return dropped;
}

ActorActionUPtr DropAction::clone()
{
  DropActionUPtr cloned = std::make_unique<DropAction>(_toDrop, _amount);
  cloned->_performer = _performer;

  return std::move(cloned);
}

void DropAction::dropOnMap(ActorPtr item)
{
  MapPtr map = _performer->getMap();
  if ( map )
  {
    item->setPosition( _performer->getX(), _performer->getY() );
    map->addActor( item );
    Messenger::message()->actorDropped(_performer, item, _amount);
  }
}

}
