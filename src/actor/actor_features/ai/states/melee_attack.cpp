#include "melee_attack.h"
#include <attack_action.h>
#include <ai.h>
#include <actor.h>
#include <unequip_action.h>
#include <equip_action.h>

namespace amarlon { namespace state {

MeleeAttack::MeleeAttack()
{
}

FSMStateType MeleeAttack::getType() const
{
  return FSMStateType::MELEE_ATTACK;
}

int MeleeAttack::update()
{
  if ( _ai )
  {
    ActorPtr enemy = _ai->getTarget().firstActor();
    ActorPtr me = _ai->getOwner().lock();

    if ( me && enemy )
    {
      me->performAction( std::make_shared<AttackAction>(enemy) );
    }
  }

  return 0;
}

bool MeleeAttack::canEnter()
{
  return true;
}

void MeleeAttack::onEnter()
{
  ActorPtr me = _ai->getOwner().lock();
  WearerPtr wearer = me ? me->getFeature<Wearer>() : nullptr;
  if ( me && wearer )
  {
    ActorPtr eqWeaponA = wearer->equipped( ItemSlotType::MainHand );
    PickablePtr eqWeapon = eqWeaponA ? eqWeaponA->getFeature<Pickable>() : nullptr;
    if ( !eqWeapon || !eqWeapon->getItemType().isMeleeWeapon() )
    {
      if ( eqWeaponA ) me->performAction( new UnEquipAction(ItemSlotType::MainHand) );
      std::vector<ActorPtr> weapons = getWeapons();
      for ( ActorPtr w : weapons )
      {
        if ( me->performAction(new EquipAction(w)) == ActorActionResult::Ok )
        {
          break;
        }
      }
    }
  }
}

std::vector<ActorPtr> MeleeAttack::getWeapons()
{
  std::vector<ActorPtr> weapons;
  ActorPtr me = _ai->getOwner().lock();
  InventoryPtr inv = me ? me->getFeature<Inventory>() : nullptr;
  if ( me && inv )
  {
    weapons = inv->items([](PickablePtr p){
      return p->getItemType().isMeleeWeapon();
    });
    std::sort(weapons.begin(), weapons.end(), [](ActorPtr l, ActorPtr r){
      PickablePtr pl = l ? l->getFeature<Pickable>() : nullptr;
      PickablePtr pr = r ? r->getFeature<Pickable>() : nullptr;
      return pl->getDamage() > pr->getDamage();
    });
  }
  return weapons;
}

}}
