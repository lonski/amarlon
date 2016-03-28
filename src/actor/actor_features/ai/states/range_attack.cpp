#include "range_attack.h"
#include <shot_action.h>
#include <ai.h>
#include <actor.h>
#include <equip_action.h>
#include <unequip_action.h>

namespace amarlon { namespace state {

RangeAttack::RangeAttack()
{
}

FSMStateType RangeAttack::getType() const
{
  return FSMStateType::ATTACK_RANGE;
}

int RangeAttack::update()
{
  if ( _ai )
  {
    ActorPtr enemy = _ai->getTarget().firstActor();
    ActorPtr me = _ai->getOwner().lock();

    if ( me && enemy )
    {
      me->performAction( std::make_shared<ShotAction>(enemy) );
    }
  }

  return 0;
}

bool RangeAttack::canEnter()
{
  _weapon = nullptr;
  _amunition = nullptr;

  ActorPtr me = _ai->getOwner().lock();
  if ( me )
  {
    me->performAction( new UnEquipAction(ItemSlotType::MainHand) );
    me->performAction( new UnEquipAction(ItemSlotType::Amunition) );
  }

  chooseWeapon();
  return _weapon && _amunition;
}

void RangeAttack::onEnter()
{
  equip();
}

void RangeAttack::chooseWeapon()
{
  auto wps = getWeapons();
  for ( ActorPtr w : wps )
  {
    auto ams = getAmunition(w->getFeature<Pickable>());
    if ( !ams.empty() )
    {
      _weapon = w;
      _amunition = ams.front();
      break;
    }
  }
}

void RangeAttack::equip()
{
  ActorPtr me = _ai->getOwner().lock();
  if ( me )
  {
    me->performAction( new UnEquipAction(ItemSlotType::MainHand) );
    me->performAction( new UnEquipAction(ItemSlotType::Amunition) );
    me->performAction( new EquipAction(_weapon) );
    me->performAction( new EquipAction(_amunition) );
  }
}

bool RangeAttack::isOutOfAmmo()
{
  bool ooa = true;
  if ( _amunition )
  {
    PickablePtr ammo = _amunition->getFeature<Pickable>();
    ooa = !ammo || ammo->getAmount() == 0;
  }
  return ooa;
}

std::vector<ActorPtr> RangeAttack::getWeapons()
{
  std::vector<ActorPtr> weapons;
  ActorPtr me = _ai->getOwner().lock();
  InventoryPtr inv = me ? me->getFeature<Inventory>() : nullptr;
  if ( me && inv )
  {
    weapons = inv->items([](PickablePtr p){
      return p->getItemType().isRangeWeapon();
    });
  }
  return weapons;
}

std::vector<ActorPtr> RangeAttack::getAmunition(PickablePtr weapon)
{
  std::vector<ActorPtr> amunition;
  ActorPtr me = _ai->getOwner().lock();
  InventoryPtr inv = me ? me->getFeature<Inventory>() : nullptr;
  if ( me && inv && weapon )
  {
    amunition = inv->items([&weapon](PickablePtr p){
      return p->getCategory() == PickableCategory::Amunition &&
             p->getItemType().amunition == weapon->getItemType().amunition;
    });
    std::sort(amunition.begin(), amunition.end(), [](ActorPtr l, ActorPtr r){
      PickablePtr pl = l ? l->getFeature<Pickable>() : nullptr;
      PickablePtr pr = r ? r->getFeature<Pickable>() : nullptr;
      return pl->getDamage() > pr->getDamage();
    });
  }
  return amunition;
}


}}
