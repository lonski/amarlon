#include "messenger.h"
#include "gui/gui.h"
#include "actor/actor.h"
#include "utils/utils.h"

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

void Messenger::actorHit(ActorPtr atacker, ActorPtr victim, int amount)
{
  if ( _gui )
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
}

void Messenger::actorMissed(ActorPtr atacker, ActorPtr victim)
{
  if ( _gui )
  {
    string msg = atacker->getName() + " missed " + tolowers(victim->getName() + ".");
    _gui->message(msg, TCODColor::darkerYellow);
  }
}

void Messenger::actorDies(ActorPtr victim)
{
  if ( _gui )
  {
    string msg = victim->getName() + " dies.";
    _gui->message(msg, TCODColor::darkerRed);
  }
}

void Messenger::actorPutInto(const std::string& putterName,
                             const string& container,
                             const std::string& itemName,
                             int amount)
{
  if ( _gui )
  {
    string msg = putterName + " put " + tolowers(itemName);

    if (amount > 1)
      msg += " (" + to_string(amount) + ")";

    msg += " into " + tolowers(container);

    _gui->message(msg+".", TCODColor::darkYellow);
  }
}

void Messenger::actorPicked(const std::string& pickerName, const std::string& itemName, int amount, const string &from)
{
  if ( _gui )
  {
    string msg = pickerName + " picked " + tolowers(itemName);

    if (amount > 1)
      msg += " (" + to_string(amount) + ")";

    if (!from.empty())
      msg += " from " + tolowers(from);

    _gui->message(msg+".", TCODColor::darkYellow);
  }
}

void Messenger::actorDropped(ActorPtr dropper, ActorPtr dropped, int amount)
{
  if ( _gui )
  {
    string msg = dropper->getName() + " dropped " + tolowers(dropped->getName());

    if (amount > 1)
      msg += " (" + to_string(amount) + ").";
    else
      msg += ".";

    _gui->message(msg, TCODColor::darkYellow);
  }
}

void Messenger::actorPicked(ActorPtr picker, ActorPtr picked, int amount)
{
  if ( _gui )
  {
    actorPicked(picker->getName(), picked->getName(), amount);
  }
}

void Messenger::actorHealed(ActorPtr healed, int amount)
{
  if ( _gui )
  {
    string msg = healed->getName() + " has been healed for " + to_string(amount) + ".";

    _gui->message(msg, TCODColor::lighterBlue);
  }
}

void Messenger::actorHasBeenLocked(ActorPtr locker, ActorPtr locked)
{
  if ( _gui )
  {
    string msg = locker->getName() + " has locked the " + tolowers(locked->getName());
    _gui->message(msg);
  }
}

void Messenger::actorHasBeenUnLocked(ActorPtr unlocker, ActorPtr unlocked)
{
  if ( _gui )
  {
    string msg = unlocker->getName() + " has unlocked the " + tolowers(unlocked->getName());
    _gui->message(msg);
  }
}

}
