#include "item_picker.h"
#include "Actor/Actor.h"
#include <gui/window/amount_window.h>
#include <utils/messenger.h>
#include <iostream>
#include <gui/message_box.h>

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
      _toPick = _toPick->afPickable()->spilt(amount);
    }
  }

  if ( _picker->afContainer()->add(_toPick) )
  {
    Messenger::message()->actorPicked(_picker->getName(), itemName, amount);
  }
  else
  {
    //rollback spilting
    if ( stackable && pickableTmp != _toPick ) pickableTmp->afPickable()->incAmount( amount );
    amount = 0;

    gui::msgError("Cannot pick up "+itemName+":\nnot enough space in inventory.");
  }

  return amount;
}


}
