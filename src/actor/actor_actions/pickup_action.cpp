#include "pickup_action.h"
#include <actor.h>

namespace amarlon{

PickUpAction::PickUpAction(ActorPtr toPick, int amount, ContainerPtr sourceContainer)
  : _toPick(toPick)
  , _amount(amount)
  , _sourceContainer(sourceContainer)
{
}

PickUpAction::~PickUpAction()
{
}

bool PickUpAction::perform(ActorPtr performer)
{
  bool picked = false;
  _performer = performer;

  PickablePtr pickable = _toPick->getFeature<Pickable>();
  if ( pickable )
  {
    if ( pickable->isStackable() && _amount < pickable->getAmount() )
    {
      picked = pickUpAmount();
    }
    else
    {
      picked = pickUpAll();
    }
  }

  return picked;
}

ActorActionUPtr PickUpAction::clone()
{
  PickUpActionUPtr cloned = std::make_unique<PickUpAction>(_toPick, _amount, _sourceContainer);
  cloned->_performer = _performer;

  return std::move(cloned);
}

bool PickUpAction::pickUpAmount()
{
  bool picked = false;

  PickablePtr pickable = _toPick->getFeature<Pickable>();
  ActorPtr splitedItem = pickable->spilt(_amount);

  if ( _performer->getFeature<Container>()->add(splitedItem) )
  {
    picked = true;
  }
  else //can't pickup - rollback
  {
    pickable->setAmount( pickable->getAmount() + _amount );
  }

  return picked;
}

bool PickUpAction::pickUpAll()
{
  bool picked = false;

  if ( _performer->getFeature<Container>()->add(_toPick) )
  {
    if ( _sourceContainer ) _sourceContainer->remove(_toPick);
    picked = true;
  }

  return picked;
}

}
