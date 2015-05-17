#include "item_action.h"
#include "actor/actor.h"
#include "actor/actor_features/container.h"
#include "gui/window/amount_window.h"
#include "gui/message_box.h"
#include "utils/amarlon_except.h"
#include <messenger.h>
#include <map.h>

namespace amarlon {

ItemAction::ItemAction(ActorPtr executor, ActorPtr targetItem, ContainerPtr sourceContainer)
  : _executor(executor)
  , _targetItem(targetItem)
  , _sourceFrom(sourceContainer)
{
}

int ItemAction::pick()
{
  bool stackable = _targetItem->getFeature<Pickable>()->isStackable();
  int amount = _targetItem->getFeature<Pickable>()->getAmount();

  //handle stackable
  if ( stackable )
  {
    int enteredAmount = askForAmount(amount);
    if (enteredAmount < amount)
    {      
      ActorPtr splitedItem = _targetItem->getFeature<Pickable>()->spilt(enteredAmount);
      if ( _executor->getFeature<Container>()->add(splitedItem) )
      {
        amount = enteredAmount;
      }
      else //can't pickup - rollback
      {
        _targetItem->getFeature<Pickable>()->setAmount(amount);
        throw inventory_full("", _targetItem->getName());
      }
    }
    else
    {
      pickUpAll();
    }
  }
  //non-stackable
  else
  {
    pickUpAll();
  }

  return amount;
}

int ItemAction::askForAmount(int defaultAmount)
{
  return Engine::instance().windowManager()
                           .getWindow<gui::AmountWindow>()
                           .setMaxAmount(defaultAmount)
                           .show()
                           .downcast<gui::AmountWindow>()
                           .getAmount();
}

void ItemAction::pickUpAll()
{
  if ( _executor->getFeature<Container>()->add(_targetItem) )
  {
    if ( _sourceFrom ) _sourceFrom->remove(_targetItem);
  }
  else
  {
    throw inventory_full("", _targetItem->getName());
  }
}

int ItemAction::drop()
{
  bool stackable = _targetItem->getFeature<Pickable>()->isStackable();
  int amount = _targetItem->getFeature<Pickable>()->getAmount();

  //handle stackable
  if ( stackable )
  {
    int enteredAmount = askForAmount(amount);
    if (enteredAmount < amount)
    {
      dropOnMap( _targetItem->getFeature<Pickable>()->spilt(enteredAmount) );
    }
    else
    {
      dropOnMap(_targetItem);
      _executor->getFeature<Container>()->remove(_targetItem);
    }
  }
  //non-stackable
  else
  {
    dropOnMap(_targetItem);
    _executor->getFeature<Container>()->remove(_targetItem);
  }

  return amount;
}

void ItemAction::dropOnMap(ActorPtr item)
{
  item->setX( _executor->getX() );
  item->setY( _executor->getY() );
  Messenger::message()->actorDropped(_executor, item, item->getFeature<Pickable>()->getAmount());
  Engine::instance().currentMap().addActor( item );
}


}
