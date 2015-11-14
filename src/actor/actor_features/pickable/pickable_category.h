#ifndef PICKABLE_CATEGORY_H
#define PICKABLE_CATEGORY_H

namespace amarlon {

enum class PickableCategory
{
  Miscellaneous = 0,
  Weapon = 1,
  Armor = 2,
  Jewelery = 3,
  Potion = 4,
  Scroll = 5,
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
          "Potion",
          "Scroll",
          "Amunition",
          "Wealth"
          }[(int)cat];
}

}

#endif // PICKABLE_CATEGORY_H
