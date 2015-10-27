#ifndef PICKABLE_DESCRIPTION
#define PICKABLE_DESCRIPTION

#include <damage.h>
#include <target_type.h>
#include <pickable_category.h>
#include <item_slot_type.h>
#include <description.h>
#include <item_type.h>

namespace amarlon {

struct PickableDescription : Description
{
  PickableDescription()
    : stackable(false)
    , amount(1)
    , uses(0)
    , itemSlot(ItemSlotType::Null)
    , armorClass(0)
    , weight(0)
    , price(0)
    , targetType(TargetType::SINGLE_NEIGHBOUR)
    , scriptId(0)
    , range(0)
    , radius(0)
  {}

  bool stackable;
  int amount;
  int uses;

  ItemSlotType itemSlot;
  int armorClass;
  int weight;
  int price;
  TargetType targetType;
  Damage damage;
  int scriptId;
  ItemType type;
  int range;
  int radius;
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

