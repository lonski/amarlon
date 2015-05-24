#include "equip_action.h"
#include <actor.h>
#include <item_slot_type.h>

namespace amarlon{

EquipAction::EquipAction(ActorPtr toEquip)
  : _toEquip(toEquip)
  , _result(EquipResult::Nok)
{
}

EquipAction::~EquipAction()
{
}

bool EquipAction::perform(ActorPtr performer)
{
  _performer = performer;
  _result = EquipResult::Nok;

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
          _result = EquipResult::Ok;
        }
      }
      else
      {
        _result = EquipResult::AlreadyEquiped;
      }
    }
    else
    {
      _result = EquipResult::NoProperSlot;
    }
  }

  return _result == EquipResult::Ok;
}

ActorActionUPtr EquipAction::clone()
{
  EquipActionUPtr cloned = std::make_unique<EquipAction>(_toEquip);
  cloned->_performer = _performer;
  cloned->_result = _result;

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
  ContainerPtr container = _performer->getFeature<Container>();
  if ( container )
  {
    container->remove(_toEquip);
  }
}

EquipResult EquipAction::getResult() const
{
  return _result;
}

}
