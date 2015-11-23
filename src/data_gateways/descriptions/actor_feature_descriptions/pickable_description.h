#ifndef PICKABLE_DESCRIPTION
#define PICKABLE_DESCRIPTION

#include <description.h>
#include <experimental/optional>

namespace amarlon {

struct PickableDescription : Description
{
  std::experimental::optional<bool> stackable;
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

};

struct ScrollDescription : PickableDescription
{
  ScrollDescription()
    : spellId(0)
  {}

  int spellId;
};

typedef std::shared_ptr<PickableDescription> PickableDescriptionPtr;
typedef std::shared_ptr<ScrollDescription> ScrollDescriptionPtr;

}

#endif // PICKABLE_DESCRIPTION

