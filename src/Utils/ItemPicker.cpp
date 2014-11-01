#include "ItemPicker.h"
#include "Actor/Actor.h"
#include "Gui/AmountWindow.h"
#include <Utils/Messenger.h>
#include <iostream>

namespace amarlon {

ItemPicker::ItemPicker(Actor* picker, Actor*& toPick)
  : _picker(picker)
  , _toPick(toPick)
{
}

int ItemPicker::pick()
{
  bool stackable = _toPick->afPickable()->isStackable();
  int amount = _toPick->afPickable()->getAmount();
  std::string itemName = _toPick->getName(); //'cause it is possible that the item does not exists after pickin' up

  if ( stackable && amount > 1)
  {
    int tmpAmount = gui::AmountWindow(amount).getAmount();

    if (tmpAmount < amount)
    {
      amount = tmpAmount;
      _toPick = _toPick->afPickable()->spilt(amount);
    }
  }

  if ( _picker->afContainer()->add(_toPick) )
  {
    Messenger::message()->actorPicked(_picker->getName(), itemName, amount);
  }
  else
  {
    amount = 0;
  }

  return amount;
}


}
