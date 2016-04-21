#include "equip_action.h"
#include <actor.h>
#include <item_slot_type.h>
#include <race.h>

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

  WearerPtr wearer = _performer->getFeature<Wearer>();
  if ( wearer )
  {
    ItemSlotType slot = aquireItemSlotType();

    if ( !wearer->hasSlot(slot) )
      return ActorActionResult::NoProperSlot;

    if ( wearer->isBlocked(slot) )
      return ActorActionResult::SlotBlocked;

    if ( wearer->isEquipped(slot) )
      return ActorActionResult::AlreadyEquiped;

    CharacterPtr c = _performer->getFeature<Character>();
    PickablePtr  p = _toEquip->getFeature<Pickable>();

    if ( !c || !p )
      return ActorActionResult::InvalidObject;

    WeaponSize weaponSize = p->getItemType().weaponSize;
    RaceType raceType = c->getRace()->getType();

    //Halfling cannot equip large weapons
    if ( slot       == ItemSlotType::MainHand &&
         weaponSize == WeaponSize::Size_L     &&
         raceType   == RaceType::Halfling )
      return ActorActionResult::Nok;

    //Equip large (or medium for halfling) weapons as 2H
    if (  weaponSize == WeaponSize::Size_L ||
         (raceType   == RaceType::Halfling && weaponSize == WeaponSize::Size_M) )
      wearer->setBlocked(ItemSlotType::Offhand, true);

    if ( wearer->equip(_toEquip) )
    {
      removeFromInventory();
      return ActorActionResult::Ok;
    }

  }

  return ActorActionResult::InvalidObject;
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

