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
  if (_msg == nullptr)
    _msg = new Messenger;

  return _msg;
}

void Messenger::setGui(gui::Gui *gui)
{
  _gui = gui;
}

void Messenger::actorHit(Actor *atacker, Actor *victim, int amount)
{
  string msg = atacker->getName() + " hits " + tolowers(victim->getName());

  if (amount > 0)
  {
    msg += " for " + to_string(amount) + "hp.";
  }
  else
  {
    msg += " but the attack took no effect.";
  }

  _gui->message(msg, TCODColor::darkRed);
}

void Messenger::actorDies(Actor *victim)
{
  string msg = victim->getName() + " dies.";
  _gui->message(msg, TCODColor::darkerRed);
}

void Messenger::actorPutInto(const std::string& putterName,
                             const string& container,
                             const std::string& itemName,
                             int amount)
{
  string msg = putterName + " put " + tolowers(itemName);

  if (amount > 1)
    msg += " (" + to_string(amount) + ")";

  msg += " into " + tolowers(container);

  _gui->message(msg+".", TCODColor::darkYellow);
}

void Messenger::actorPicked(const std::string& pickerName, const std::string& itemName, int amount, const string &from)
{
  string msg = pickerName + " picked " + tolowers(itemName);

  if (amount > 1)
    msg += " (" + to_string(amount) + ")";

  if (!from.empty())
    msg += " from " + tolowers(from);

  _gui->message(msg+".", TCODColor::darkYellow);
}

void Messenger::actorDropped(Actor *dropper, Actor *dropped, int amount)
{
  string msg = dropper->getName() + " dropped " + tolowers(dropped->getName());

  if (amount > 1)
    msg += " (" + to_string(amount) + ").";
  else
    msg += ".";

  _gui->message(msg, TCODColor::darkYellow);
}

void Messenger::actorPicked(Actor *picker, Actor *picked, int amount)
{
  actorPicked(picker->getName(), picked->getName(), amount);
}

void Messenger::actorIsLocked(Actor *openableActor)
{
  string msg = "The " + tolowers(openableActor->getName()) + " is locked.";
  _gui->message(msg);
}

void Messenger::actorHealed(Actor *healed, int amount)
{
  string msg = healed->getName() + " has been healed for " + to_string(amount) + ".";

  _gui->message(msg, TCODColor::lighterBlue);
}

void Messenger::actorHasBeenLocked(Actor *locker, Actor *locked)
{
  string msg = locker->getName() + " has locked the " + tolowers(locked->getName());
  _gui->message(msg);
}

void Messenger::actorHasBeenUnLocked(Actor *unlocker, Actor *unlocked)
{
  string msg = unlocker->getName() + " has unlocked the " + tolowers(unlocked->getName());
  _gui->message(msg);
}

void Messenger::actorNotUsable(Actor *actor)
{
  string msg = actor->getName() + " is not usable.";
  _gui->message(msg);
}

}
