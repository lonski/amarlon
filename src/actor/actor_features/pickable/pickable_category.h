#ifndef PICKABLE_CATEGORY_H
#define PICKABLE_CATEGORY_H

namespace amarlon {

enum class PickableCategory
{
  NoCategory = 0,
  Miscellaneous = 1,
  Weapon = 2,
  Armor = 3,
  Jewelery = 4,
  Potion = 5,
  Scroll = 6,
  Amunition = 7,
  Wealth = 8
};

static inline const char* PickableCategory2Str(PickableCategory cat)
{
  return (const char *[]){
          "Uncategorized",
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
