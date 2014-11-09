#include "messenger.h"
#include "gui/gui.h"
#include "Actor/Actor.h"
#include <utils/utils.h>

namespace amarlon {

using namespace std;

Messenger* Messenger::_msg(nullptr);

Messenger::Messenger()
  : _gui(nullptr)
{
}

Messenger *Messenger::message()
{
  if ( _msg == nullptr )
    _msg = new Messenger;

  return _msg;
}

void Messenger::setGui(gui::Gui *gui)
{
  _gui = gui;
}

void Messenger::actorHit(Actor *atacker, Actor *victim, int amount)
{
  string aName = atacker->getName();
  string vName = tolowers(victim->getName());
  string msg = aName + " hits " + vName;

  if ( amount > 0)
  {
    msg = msg + " for " + to_string(amount) + "hp.";
  }
  else
  {
    msg = msg + " but the attack took no effect.";
  }

  _gui->message(msg, TCODColor::darkRed);
}

void Messenger::actorDies(Actor *victim)
{
  string vName = victim->getName();
  string msg = vName + " dies.";

  _gui->message(msg, TCODColor::darkerRed);
}

void Messenger::actorPicked(std::string pickerName, std::string itemName, int amount)
{
  string msg = pickerName + " picked " + tolowers(itemName);

  if (amount > 1)
    msg += " (" + to_string(amount) + ").";
  else
    msg += ".";

  _gui->message(msg, TCODColor::darkYellow);
}

void Messenger::actorDropped(Actor *dropper, Actor *dropped, int amount)
{
  string dropperName = dropper->getName();
  string itemName = dropped->getName();

  string msg = dropperName + " dropped " + tolowers(itemName);

  if (amount > 1)
    msg += " (" + to_string(amount) + ").";
  else
    msg += ".";

  _gui->message(msg, TCODColor::darkYellow);
}

void Messenger::actorPicked(Actor *picker, Actor *picked, int amount)
{
  string pickerName = picker->getName();
  string itemName = picked->getName();

  actorPicked(pickerName, itemName, amount);
}

void Messenger::actorIsLocked(Actor *openableActor)
{
  string oName = tolowers(openableActor->getName());
  string msg = "The " + oName + " is locked.";

  _gui->message(msg);
}

void Messenger::actorHealed(Actor *healed, int amount)
{
  string hName = healed->getName();
  string msg = hName + " has been healed for " + to_string(amount) + ".";

  _gui->message(msg, TCODColor::lighterBlue);
}

void Messenger::actorHasBeenLocked(Actor *locker, Actor *locked)
{
  string eName = locker->getName();
  string tName = tolowers(locked->getName());
  string msg = eName + " has locked the " + tName;

  _gui->message(msg);
}

void Messenger::actorHasBeenUnLocked(Actor *unlocker, Actor *unlocked)
{
  string eName = unlocker->getName();
  string tName = tolowers(unlocked->getName());
  string msg = eName + " has unlocked the " + tName;

  _gui->message(msg);
}

void Messenger::actorNotUsable(Actor *actor)
{
  string eName = actor->getName();
  string msg = eName + " is not usable.";

  _gui->message(msg);
}

}
