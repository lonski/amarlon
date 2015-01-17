#include "item_picker.h"
#include "Actor/Actor.h"
#include <gui/window/amount_window.h>
#include <utils/amarlon_except.h>
#include <gui/message_box.h>
#include <Actor/ActorFeatures/container.h>

namespace amarlon {

ItemPicker::ItemPicker(Actor* picker, Actor*& toPick, Container *pickedFrom)
  : _picker(picker)
  , _toPick(toPick)
  , _pickedFrom(pickedFrom)
{
}

int ItemPicker::pick()
{
  bool stackable = _toPick->getFeature<Pickable>()->isStackable();
  int amount = _toPick->getFeature<Pickable>()->getAmount();
  std::string itemName = _toPick->getName(); //'cause it is possible that the item does not exists after pickin' up
  Actor* pickableTmp = _toPick; //to rollback spilting amount, when cant pickup (container full)

  if ( stackable && amount > 1)
  {
    int tmpAmount = Engine::instance().windowManager()
                                      .getWindow<gui::AmountWindow>()
                                      .setMaxAmount(amount)
                                      .show()
                                      .downcast<gui::AmountWindow>()
                                      .getAmount();

    if (tmpAmount < amount)
    {
      amount = tmpAmount;
      _toPick = _toPick->getFeature<Pickable>()->spilt(amount);
    }
  }

  if ( _picker->getFeature<Container>()->add(_toPick) )
  {
    if ( _pickedFrom ) _pickedFrom->remove(_toPick);
  }
  else //cant pick up!
  {
    //rollback spilting
    if ( stackable && pickableTmp != _toPick ) pickableTmp->getFeature<Pickable>()->incAmount( amount );
    amount = 0;

    throw inventory_full("", itemName);
  }

  return amount;
}


}
