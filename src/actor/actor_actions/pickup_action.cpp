#include "pickup_action.h"
#include <actor.h>

namespace amarlon{

PickUpAction::PickUpAction(ActorPtr toPick, int amount, std::function<void(ActorPtr)> removeAction )
  : _toPick(toPick)
  , _amount(amount)
  , _removeAction(removeAction)
{
}

PickUpAction::~PickUpAction()
{
}

ActorActionResult PickUpAction::perform(ActorPtr performer)
{
  ActorActionResult r = ActorActionResult::Nok;
  _performer = performer;

  PickablePtr pickable = _toPick->getFeature<Pickable>();
  if ( pickable )
  {
    if ( pickable->isStackable() && _amount < pickable->getAmount() )
    {
      r = pickUpAmount();
    }
    else
    {
      r = pickUpAll();
    }
  }

  if ( r == ActorActionResult::Ok )
  {
    _performer->notify(Event(EventId::Actor_Pick,{{"name", _toPick->getName()}}));
  }

  return r;
}

ActorActionUPtr PickUpAction::clone()
{
  PickUpActionUPtr cloned = std::make_unique<PickUpAction>(_toPick, _amount, _removeAction);
  cloned->_performer = _performer;

  return std::move(cloned);
}

ActorActionResult PickUpAction::pickUpAmount()
{
  ActorActionResult r = ActorActionResult::Nok;

  PickablePtr pickable = _toPick->getFeature<Pickable>();
  ActorPtr splitedItem = pickable->spilt(_amount);

  if ( _performer->getFeature<Inventory>()->add(splitedItem) )
  {
    r = ActorActionResult::Ok;
  }
  else //can't pickup - rollback
  {
    pickable->setAmount( pickable->getAmount() + _amount );
  }

  return r;
}

ActorActionResult PickUpAction::pickUpAll()
{
  ActorActionResult r = ActorActionResult::Nok;

  if ( _performer->getFeature<Inventory>()->add(_toPick) )
  {
    _removeAction(_toPick);
    r = ActorActionResult::Ok;
  }

  return r;
}

}

