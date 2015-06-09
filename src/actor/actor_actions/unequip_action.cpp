#include "unequip_action.h"
#include <actor.h>

namespace amarlon {

UnEquipAction::UnEquipAction(ActorPtr toUnEquip)
  : _toUnEquip(toUnEquip)
  , _result(UnEquipResult::Nok)
  , _slot(ItemSlotType::Null)
{
}

UnEquipAction::UnEquipAction(ItemSlotType slot)
  : _result(UnEquipResult::Nok)
  , _slot(slot)
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

ActorActionUPtr UnEquipAction::clone()
{
  UnEquipActionUPtr cloned = std::make_unique<UnEquipAction>(_toUnEquip);
  cloned->_slot = _slot;
  cloned->_performer = _performer;
  cloned->_result = _result;

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

UnEquipResult UnEquipAction::getResult() const
{
  return _result;
}

}
