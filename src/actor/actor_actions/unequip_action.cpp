#include "unequip_action.h"
#include <actor.h>

namespace amarlon {

UnEquipAction::UnEquipAction(ActorPtr toUnEquip)
  : _toUnEquip(toUnEquip)
  , _slot(ItemSlotType::Null)
{
}

UnEquipAction::UnEquipAction(ItemSlotType slot)
  : _slot(slot)
{
}


UnEquipAction::~UnEquipAction()
{
}

ActorActionResult UnEquipAction::perform(ActorPtr performer)
{
  _performer = performer;
  aquireItemSlotType();

  if ( _slot == ItemSlotType::Null )
    return ActorActionResult::Nok;

  WearerPtr wearer = _performer->getFeature<Wearer>();

  if ( !wearer )
    return ActorActionResult::Nok;

  ActorPtr equippedItem = wearer->equipped(_slot);

  if ( !equippedItem )
    return ActorActionResult::NotEquipped;

  if ( equippedItem->getFeature<Pickable>()->isCursed() )
    return ActorActionResult::CursedItem;

  ActorPtr unequipped = wearer->unequip( _slot );
  InventoryPtr inventory = performer->getFeature<Inventory>();

  if ( !inventory )
    return ActorActionResult::Nok;

  if ( !inventory->add(unequipped) )
  {
    wearer->equip(unequipped);
    return ActorActionResult::InventoryFull;
  }

  if ( _slot == ItemSlotType::MainHand && wearer->isBlocked(ItemSlotType::Offhand) )
    wearer->setBlocked(ItemSlotType::Offhand, false);

  return ActorActionResult::Ok;
}

ActorActionUPtr UnEquipAction::clone()
{
  UnEquipActionUPtr cloned = std::make_unique<UnEquipAction>(_toUnEquip);
  cloned->_slot = _slot;
  cloned->_performer = _performer;

  return std::move(cloned);
}

void UnEquipAction::aquireItemSlotType()
{
  if ( _toUnEquip )
  {
    PickablePtr pickable = _toUnEquip->getFeature<Pickable>();
    if ( pickable )
    {
      _slot = pickable->getItemSlot();
    }
  }
}

}

