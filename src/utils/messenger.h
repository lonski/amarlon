#ifndef MESSENGER_H
#define MESSENGER_H

#include <string>

namespace amarlon {

namespace gui {
  class Gui;
}
class Actor;

class Messenger
{
public:
  static Messenger* message();

  void setGui(gui::Gui* gui);

  void actorHit(Actor* atacker, Actor* victim, int amount);
  void actorDies(Actor* victim);
  void actorPicked(Actor* picker, Actor* picked, int amount);
  void actorPicked(const std::string& pickerName, const std::string& itemName, int amount, const std::string& from = "");
  void actorDropped(Actor* dropper, Actor* dropped, int amount);
  void actorHealed(Actor* healed, int amount);
  void actorHasBeenLocked(Actor* locker, Actor* locked);
  void actorHasBeenUnLocked(Actor* unlocker, Actor* unlocked);
  void actorPutInto(const std::string& putterName, const std::string& container, const std::string& itemName, int amount);

private:
  Messenger();
  Messenger& operator=(const Messenger&);

  static Messenger* _msg;
  gui::Gui* _gui;

};

}

#endif // MESSENGER_H
