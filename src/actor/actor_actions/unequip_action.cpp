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

bool UnEquipAction::perform(ActorPtr performer)
{
  _result = UnEquipResult::Nok;
  _performer = performer;
  aquireItemSlotType();

  if ( _slot != ItemSlotType::Null )
  {
    WearerPtr wearer = _performer->getFeature<Wearer>();
    if ( wearer && wearer->isEquipped( _slot ) )
    {
      ActorPtr unequipped = wearer->unequip( _slot );
      ContainerPtr inventory = performer->getFeature<Container>();
      if ( inventory && inventory->add(unequipped) )
      {
        _result = UnEquipResult::Ok;
      }
      else
      {
        wearer->equip(unequipped);
        _result = UnEquipResult::InventoryFull;
      }
    }
    else
    {
      _result = UnEquipResult::NotEquipped;
    }
  }

  return _result == UnEquipResult::Ok;
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

UnEquipResult UnEquipAction::getResult() const
{
  return _result;
}

}
