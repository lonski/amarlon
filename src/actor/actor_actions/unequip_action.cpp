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
  ActorActionResult r = ActorActionResult::Nok;
  _performer = performer;
  aquireItemSlotType();

  if ( _slot != ItemSlotType::Null )
  {
    WearerPtr wearer = _performer->getFeature<Wearer>();
    if ( wearer && wearer->isEquipped( _slot ) )
    {
      ActorPtr unequipped = wearer->unequip( _slot );
      InventoryPtr inventory = performer->getFeature<Inventory>();
      if ( inventory && inventory->add(unequipped) )
      {
        r = ActorActionResult::Ok;
      }
      else
      {
        wearer->equip(unequipped);
        r = ActorActionResult::InventoryFull;
      }
    }
    else
    {
      r = ActorActionResult::NotEquipped;
    }
  }

  return r;
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

