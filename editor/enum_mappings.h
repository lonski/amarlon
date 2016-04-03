#ifndef ENUM_MAPPINGS
#define ENUM_MAPPINGS

#include <QStringList>

static QStringList char_classes = {
  "NoClass",
  "Fighter",
  "Cleric",
  "MagicUser",
  "Thief",
  "Monster"
};

static QStringList target_types = {
  "Single neighbour",
  "Single range",
  "Area range projectile",
  "Area neighbour",
  "Self",
  "Single range projectile",
  "Caster area",
  "Area range"
};

static QStringList pickable_categories = {
  "Uncategorized",
  "Miscellaneous",
  "Weapon",
  "Armor",
  "Jewelery",
  "Potion",
  "Scroll",
  "Amunition",
  "Wealth"
};

static QStringList weapon_types = {
  "NoType",
  "Sword",
  "Blunt",
  "Dagger",
  "Staff",
  "Bow"
};

static QStringList armor_types = {
  "NoType",
  "Cloth",
  "Leather"
};

static QStringList amunition_types = {
  "NoType",
  "Arrow"
};

static QStringList item_slots = {
  "None",
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
  "Arrows"
};

static QStringList races = {
  "NoRace"   ,
  "Human"    ,
  "Dwarf"    ,
  "Elf"      ,
  "Halfling" ,
  "Orc"      ,
  "Goblin"   ,
  "Undead"
};

#endif // ENUM_MAPPINGS

