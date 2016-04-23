#ifndef BASE_ITEM_DATA_H
#define BASE_ITEM_DATA_H

#include <map>
#include <vector>

namespace amarlon {

struct BaseItemData
{
  enum Type {
    Weapon,
    Armor
  };

  std::map< Type, std::vector<int> > ids;
};

static std::map<std::string, BaseItemData::Type> Str2BaseItemDataType = {
  { "Weapon", BaseItemData::Weapon },
  { "Armor",  BaseItemData::Armor }
};

}

#endif // BASE_ITEM_DATA_H
