#ifndef PICKABLE_CATEGORY_H
#define PICKABLE_CATEGORY_H

namespace amarlon {

enum class PickableCategory
{
  Miscellaneous = 0,
  Weapon = 1,
  Armor = 2,
  Jewelery = 3,
  Potions = 4,
  Scrolls = 5,
  Amunition = 6,
  Wealth = 7

};

static inline const char* PickableCategory2Str(PickableCategory cat)
{
  return (const char *[]){
          "Miscellaneous",
          "Weapon",
          "Armor",
          "Jewelery",
          "Potions",
          "Scrolls",
          "Amunition",
          "Wealth"
          }[(int)cat];
}

}

#endif // PICKABLE_CATEGORY_H
