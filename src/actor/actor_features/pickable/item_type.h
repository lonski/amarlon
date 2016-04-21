#ifndef ITEM_TYPE
#define ITEM_TYPE

#include <cstring>
#include <string>
#include <pickable_category.h>
#include <utils.h>
#include <item_type_description.h>

namespace amarlon {

enum class WeaponType
{
  NoType = 0,
  Sword  = 1,
  Blunt  = 2,
  Dagger = 3,
  Staff  = 4,
  Bow    = 5,
  Axe    = 6,
  Crossbow = 7,
  Sling    = 8
  /* When adding new types here
   * remember to fill
   * ItemType::isMeleeWeapon()
   * ItemType::isRangeWeapon()
   */
};

static inline const char* WeaponType2Str(WeaponType t)
{
  return (const char *[]){
          "NoType",
          "Sword",
          "Blunt",
          "Dagger",
          "Staff",
          "Bow"
          }[(int)t];
}

enum class WeaponSize
{
  NoSize = 0,
  Size_S = 1,
  Size_M = 2,
  Size_L = 3
};

static inline const char* WeaponSize2Str(WeaponSize t)
{
  return (const char *[]){
          "NoSize",
          "Size_S",
          "Size_M",
          "Size_L"
          }[(int)t];
}

enum class ArmorType
{
  NoType  = 0,
  Cloth   = 1,
  Light   = 2,
  Heavy   = 3
};

static inline const char* ArmorType2Str(ArmorType t)
{
  return (const char *[]){
          "NoType",
          "Cloth",
          "Leather"
          }[(int)t];
}

enum class AmunitionType
{
  NoType  = 0,
  ShortBowArrow   = 1,
  LongBowArrow    = 2,
  LightQuarrel    = 3,
  HeavyQuarrel    = 4,
  Bullet          = 5
};

static inline const char* AmunitionType2Str(AmunitionType t)
{
  return (const char *[]){
          "NoType",
          "Shortbow Arrow",
          "Longbow Arrow"
          }[(int)t];
}

struct ItemType
{
  ItemType()
  {
    memset(this, 0, sizeof(ItemType));
  }

  ItemType(ItemTypeDescription dsc)
  {
    if ( dsc.amunitionType ) amunition  = (AmunitionType)*dsc.amunitionType;
    if ( dsc.armorType )     armor      = (ArmorType)*dsc.armorType;
    if ( dsc.category )      category   = (PickableCategory)*dsc.category;
    if ( dsc.weaponType )    weapon     = (WeaponType)*dsc.weaponType;
    if ( dsc.weaponSize )    weaponSize = (WeaponSize)*dsc.weaponSize;
  }

  void merge(const ItemType& rhs)
  {
    if ( rhs.category != PickableCategory::NoCategory ) category = rhs.category;
    if ( rhs.weapon != WeaponType::NoType ) weapon = rhs.weapon;
    if ( rhs.armor != ArmorType::NoType ) armor = rhs.armor;
    if ( rhs.amunition != AmunitionType::NoType ) amunition = rhs.amunition;
    if ( rhs.weaponSize != WeaponSize::NoSize ) weaponSize = rhs.weaponSize;
  }

  bool operator==(const ItemType& rhs) const
  {
    return category == rhs.category &&
           weapon == rhs.weapon &&
           armor == rhs.armor &&
           amunition == rhs.amunition &&
           weaponSize == rhs.weaponSize;
  }

  bool isMeleeWeapon() const
  {
    return weapon == WeaponType::Blunt  ||
           weapon == WeaponType::Dagger ||
           weapon == WeaponType::Staff  ||
           weapon == WeaponType::Sword  ||
           weapon == WeaponType::Axe;

  }

  bool isRangeWeapon() const
  {
    return weapon == WeaponType::Bow ||
           weapon == WeaponType::Crossbow ||
           weapon == WeaponType::Sling;
  }

  PickableCategory category;
  WeaponType weapon;
  ArmorType armor;
  AmunitionType amunition;
  WeaponSize weaponSize;
};

class ItemTypeRestriction
{
public:
  ItemTypeRestriction(ItemType type)
    : _type(type)
  {
  }

  bool allow(ItemType type)
  {
    return type == _type;
  }

  ItemType getType() const
  {
    return _type;
  }

  std::string toString() const
  {
    std::string dsc;
    std::string cat = tolowers( PickableCategory2Str( _type.category ) );

    if ( _type.armor != ArmorType::NoType )
    {
      dsc += ArmorType2Str(_type.armor);
      dsc += " type " + cat + "s";
    }
    else if ( _type.weapon != WeaponType::NoType )
    {
      dsc += WeaponType2Str(_type.weapon);
      dsc += " type " + cat + "s";
    }
    else if ( _type.amunition != AmunitionType::NoType )
    {
      dsc += AmunitionType2Str(_type.amunition);
      dsc += " type " + cat + "s";
    }

    return dsc;
  }

private:
  ItemType _type;

};

}

#endif // ITEM_TYPE

