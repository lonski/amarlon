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

static QStringList character_types = {
  "NoType",
  "Generic",
  "PlayableCharacter"
};

static QStringList relation_teams = {
  "Monster"      ,
  "NPC"          ,
  "Player"       ,
  "PcHostileNPC"
};

static QStringList skills = {
  "Null"            ,
  "OpenLocks"       ,
  "DisarmTraps"     ,
  "Hide"            ,
  "PickPockets"     ,
  "SilentMove"      ,
  "FindTraps"       ,
  "Darkvision"      ,
  "DwarfRacial"     ,
  "ElfRacial"       ,
  "HalflingRacial"  ,
  "HumanRacial"     ,
};

static QStringList spells = {
  "Null"            ,
  "CureLightWounds" ,
  "MagicMissile"    ,
  "Fireball"        ,
  "Bless"           ,
  "Shield"          ,
  "Sleep"
};

static QStringList actors = {
  "Null",
  "Player" ,
  "Orc" ,
  "DoorClosed" ,
  "DoorOpen" ,
  "Bed" ,
  "Locker" ,
  "Wardrobe" ,
  "Chair" ,
  "Furnace" ,
  "Table" ,
  "Worktop" ,
  "BootleOfWine" ,
  "HealthPotion" ,
  "CookBook" ,
  "Corpse"  ,
  "PantryKey" ,
  "LeatherBoots" ,
  "LeatherArmor" ,
  "GoldCoin" ,
  "BlackAle" ,
  "Dagger" ,
  "Goblin" ,
  "BladeTrap" ,
  "ScrollFireball" ,
  "Toilet" ,
  "Beer" ,
  "Arrow" ,
  "ShortBow" ,
  "Tero" ,
  "ShortSword" ,
  "Arrow_P1" ,
  "End"
};

static QStringList ai_types {
    "Null" ,
    "GenericAi" ,
    "PlayerAi"
};

static QStringList trap_id {
    "Null" ,
    "BladeTrap"
};

static QStringList maps {
  "Null",
  "GameStart",
  "Test"
};

static QStringList tiles {
  "X",
  ".", //PlainFloot
  "#", //PlainWall
  "T", //Tree,
  ",", //Grass,
  "-", //Dirt,
  "=", //water
};

static QStringList tile_types {
  "None (X)",
  "PlainFloor (.)", //PlainFloot
  "PlainWall (#)", //PlainWall
  "Tree (T)", //Tree,
  "Grass (,)", //Grass,
  "Dirt (-)", //Dirt,
  "water (=)", //water
};

#endif // ENUM_MAPPINGS

