#ifndef ACTORTYPE_H
#define ACTORTYPE_H

namespace amarlon {

enum class ActorType
{
  Null,  
  Player = 1,
  Orc = 2,
  DoorClosed = 3,
  DoorOpen = 4,
  Bed = 5,
  Locker = 6,
  Wardrobe = 7,
  Chair = 8,
  Furnace = 9,
  Table = 10,
  Worktop = 11,
  BootleOfWine = 12,
  HealthPotion = 13,
  CookBook = 14,
  Corpse = 15 ,
  PantryKey = 16,
  LeatherBoots = 18,
  LeatherArmor = 20,
  GoldCoin = 22,
  BlackAle = 23,
  Dagger = 24,
  Goblin = 25,
  BladeTrap = 26,
  ScrollFireball = 27,
  Toilet = 28,
  Beer = 29,
  Arrow = 30,
  ShortBow = 31,
  Tero = 32,
  ShortSword = 33,
  End
};

}

#endif // ACTORTYPE_H
