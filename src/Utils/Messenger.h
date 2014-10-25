#ifndef MESSENGER_H
#define MESSENGER_H

namespace amarlon {

class Gui;
class Actor;

class Messenger
{
public:
  static Messenger* message();

  void setGui(Gui* gui);

  void actorHit(Actor* atacker, Actor* victim, int amount);
  void actorDies(Actor* victim);
  void actorPicked(Actor* picker, Actor* picked, int amount);
  void actorIsLocked(Actor* openableActor);
  void actorHealed(Actor* healed, int amount);
  void actorHasBeenLocked(Actor* locker, Actor* locked);
  void actorHasBeenUnLocked(Actor* unlocker, Actor* unlocked);
  void actorNotUsable(Actor* actor);

private:
  Messenger();
  Messenger& operator=(const Messenger&);

  static Messenger* _msg;
  Gui* _gui;

};

}

#endif // MESSENGER_H
