#ifndef PICKABLE_DESCRIPTION
#define PICKABLE_DESCRIPTION

#include <damage.h>
#include <target_type.h>
#include <pickable_category.h>
#include <item_slot_type.h>
#include <description.h>
#include <item_type.h>
#include <experimental/optional>

namespace amarlon {

struct PickableDescription : Description
{
  std::experimental::optional<bool> stackable;
  std::experimental::optional<int> amount;
  std::experimental::optional<int> uses;
  std::experimental::optional<ItemSlotType> itemSlot;
  std::experimental::optional<int> armorClass;
  std::experimental::optional<int> weight;
  std::experimental::optional<int> price;
  std::experimental::optional<TargetType> targetType;
  std::experimental::optional<Damage> damage;
  std::experimental::optional<int> scriptId;
  std::experimental::optional<int> range;
  std::experimental::optional<int> radius;

  ItemType type;
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

