#ifndef ITEM_TYPE
#define ITEM_TYPE

#include <cstring>
#include <string>
#include <pickable_category.h>
#include <utils.h>

namespace amarlon {

enum class WeaponType
{
  NoType = 0,
  Sword  = 1,
  Blunt  = 2,
  Dagger = 3,
  Staff  = 4,
  Bow    = 5
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

enum class ArmorType
{
  NoType  = 0,
  Cloth   = 1,
  Leather = 2
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
  Arrow   = 1
};

static inline const char* AmunitionType2Str(AmunitionType t)
{
  return (const char *[]){
          "NoType",
          "Arrow"
          }[(int)t];
}

struct ItemType
{
  ItemType()
  {
    memset(this, 0, sizeof(ItemType));
  }

  bool operator==(const ItemType& rhs) const
  {
    return category == rhs.category &&
           weapon == rhs.weapon &&
           armor == rhs.armor &&
           amunition == rhs.amunition;
  }

  PickableCategory category;
  WeaponType weapon;
  ArmorType armor;
  AmunitionType amunition;
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

