#ifndef ITEM_TYPE_DESCRIPTION
#define ITEM_TYPE_DESCRIPTION

#include <description.h>
#include <experimental/optional>

namespace amarlon {

struct ItemTypeDescription : Description
{
  std::experimental::optional<int> armorType;
  std::experimental::optional<int> weaponType;
  std::experimental::optional<int> amunitionType;
  std::experimental::optional<int> category;
  std::experimental::optional<int> weaponSize;
};

}

#endif // ITEM_TYPE_DESCRIPTION

