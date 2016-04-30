#ifndef PICKABLE_DESCRIPTION
#define PICKABLE_DESCRIPTION

#include <description.h>
#include <experimental/optional>

namespace amarlon {

struct PickableDescription : Description
{
  std::experimental::optional<bool> stackable;
  std::experimental::optional<bool> cursed;
  std::experimental::optional<int> amount;
  std::experimental::optional<int> uses;
  std::experimental::optional<int> itemSlot;
  std::experimental::optional<int> armorClass;
  std::experimental::optional<int> weight;
  std::experimental::optional<int> price;
  std::experimental::optional<int> targetType;
  std::experimental::optional<std::string> damage;
  std::experimental::optional<int> scriptId;
  std::experimental::optional<int> range;
  std::experimental::optional<int> radius;
  std::experimental::optional<int> armorType;
  std::experimental::optional<int> weaponType;
  std::experimental::optional<int> amunitionType;
  std::experimental::optional<int> category;
  std::experimental::optional<int> weaponSize;
  std::experimental::optional<int> useType;
  std::experimental::optional<int> useRestriction;
  std::experimental::optional<int> spellId;

  virtual bool any()
  {
    return stackable || amount || uses || itemSlot || armorClass ||
           weight || price || targetType || damage || scriptId ||
           range || radius || armorType || weaponType || amunitionType ||
           category || weaponSize || useType || spellId || useRestriction ||
           cursed;
  }
};

typedef std::shared_ptr<PickableDescription> PickableDescriptionPtr;

}

#endif // PICKABLE_DESCRIPTION

