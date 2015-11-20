#include "drop_action.h"
#include <actor.h>
#include <map.h>


namespace amarlon {

DropAction::DropAction(ActorPtr toDrop, int amount)
  : _toDrop(toDrop)
  , _amount(amount)
{
}

DropAction::~DropAction()
{
}

ActorActionResult DropAction::perform(ActorPtr performer)
{
  ActorActionResult r = ActorActionResult::Nok;

  if ( _toDrop )
  {
    _performer = performer;
    PickablePtr pickable = _toDrop->getFeature<Pickable>();

    if ( pickable->isStackable() && _amount < pickable->getAmount() )
    {
      dropOnMap( pickable->spilt(_amount) );
      r = ActorActionResult::Ok;
    }
    else
    {
      dropOnMap(_toDrop);
      _performer->getFeature<Inventory>()->remove(_toDrop);
      r = ActorActionResult::Ok;
    }
  }

  return r;
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
    item->setMap(nullptr);
    item->setPosition( _performer->getX(), _performer->getY() );
    map->addActor( item );
    _performer->notify(Event(EventId::Actor_Drop,{{"name",item->getName()},{"count", std::to_string(_amount)}}));
  }
}

}

