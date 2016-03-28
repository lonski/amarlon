#ifndef ITEM_SLOT_TYPE_H
#define ITEM_SLOT_TYPE_H

#include <iostream>

namespace amarlon {

enum class ItemSlotType
{
  Null = 0,

  Helmet = 1,
  Amulet = 2,
  Armor = 3,
  Belt = 4,  
  Hands = 5,
  Boots = 6,
  MainHand = 7,
  Offhand = 8,
  LeftRing = 9,
  RightRing = 10,
  Cloak = 11,
  Amunition = 12,

  End = 13
};

inline ItemSlotType operator++(ItemSlotType& x) { return x = (ItemSlotType)(std::underlying_type<ItemSlotType>::type(x) + 1); }
inline ItemSlotType operator*(ItemSlotType c) {return c;}
inline ItemSlotType begin(ItemSlotType) {return ItemSlotType::Null;}
inline ItemSlotType end(ItemSlotType)   {return ItemSlotType::End;}

static inline const char* ItemSlotType2Str(ItemSlotType slot)
{
  return (const char *[]){
          "Invalid-Null",

          "Helmet",
          "Amulet",
          "Body",
          "Belt",
          "Hands",
          "Boots",
          "Main hand",
          "Offhand",
          "Left ring",
          "Right ring",
          "Cloak",
          "Arrows",

          "Invalid-End"
          }[(int)slot];
}

static inline const char* ItemSlotType2Str(int slot)
{
  return ItemSlotType2Str(static_cast<ItemSlotType>(slot));
}


}

#endif // ITEM_SLOT_TYPE_H
