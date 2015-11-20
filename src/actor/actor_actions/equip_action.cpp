#include "equip_action.h"
#include <actor.h>
#include <item_slot_type.h>

namespace amarlon{

EquipAction::EquipAction(ActorPtr toEquip)
  : _toEquip(toEquip)
{
}

EquipAction::~EquipAction()
{
}

ActorActionResult EquipAction::perform(ActorPtr performer)
{
  _performer = performer;
  ActorActionResult r = ActorActionResult::Nok;

  WearerPtr wearer = _performer->getFeature<Wearer>();
  if ( wearer )
  {
    ItemSlotType slot = aquireItemSlotType();
    if ( wearer->hasSlot( slot ) )
    {
      if ( !wearer->isEquipped(slot) )
      {
        if ( wearer->equip(_toEquip) )
        {
          removeFromInventory();
          r = ActorActionResult::Ok;
        }
      }
      else
      {
        r = ActorActionResult::AlreadyEquiped;
      }
    }
    else
    {
      r = ActorActionResult::NoProperSlot;
    }
  }

  return r;
}

ActorActionUPtr EquipAction::clone()
{
  EquipActionUPtr cloned = std::make_unique<EquipAction>(_toEquip);
  cloned->_performer = _performer;

  return std::move(cloned);
}

ItemSlotType EquipAction::aquireItemSlotType()
{
  ItemSlotType slot = ItemSlotType::Null;

  PickablePtr pickable = _toEquip->getFeature<Pickable>();
  if ( pickable )
  {
    slot = pickable->getItemSlot();
  }

  return slot;
}

void EquipAction::removeFromInventory()
{
  InventoryPtr container = _performer->getFeature<Inventory>();
  if ( container )
  {
    container->remove(_toEquip);
  }
}

}

