#include "range_attack.h"
#include <shot_action.h>
#include <ai.h>
#include <actor.h>
#include <equip_action.h>

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
      //TODO manage out of ammo
      me->performAction( std::make_shared<ShotAction>(enemy) );
    }
  }

  return 0;
}

bool RangeAttack::canEnter()
{
  bool canEnter = false;
  if ( _ai && _ai->getOwner().lock() )
  {
    ActorPtr me = _ai->getOwner().lock();
    WearerPtr wearer = me ? me->getFeature<Wearer>() : nullptr;

    if ( me && wearer )
    {
      wearer->unequip(ItemSlotType::MainHand);
      wearer->unequip(ItemSlotType::Amunition);

      auto wps = getWeapons();
      for ( ActorPtr w : wps )
      {
        auto ams = getAmunition(w->getFeature<Pickable>());
        if ( !ams.empty() )
        {
          _weapon = w;
          _amunition = ams.front();
          canEnter = true;
          break;
        }
      }
    }
  }
  return canEnter;
}

void RangeAttack::onEnter()
{
  ActorPtr me = _ai->getOwner().lock();
  if ( me )
  {
    me->performAction( new EquipAction(_weapon) );
    me->performAction( new EquipAction(_amunition) );
  }
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
  }
  return amunition;
}


}}
