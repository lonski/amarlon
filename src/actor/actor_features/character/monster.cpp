#include "monster.h"
#include <actor.h>
#include <die_action.h>
#include <attack_bonus_table.h>
#include <iostream>
#include <utils.h>
#include <actor_descriptions.h>
#include <race.h>
#include <actor.h>

namespace amarlon {

Monster::Monster()
{
}

Monster::Monster(DescriptionPtr dsc)
  : Character(dsc)
{
  MonsterDescriptionPtr mDsc = std::dynamic_pointer_cast<MonsterDescription>(dsc);
  if ( mDsc != nullptr )
  {
    _morale = mDsc->morale;
    _hpMod = mDsc->hitPointsBonus;
    _damage = mDsc->damage;
    setLevel( mDsc->level );    
    setMaxHitPoints( (static_cast<int>(dices::D8) * getLevel()) + mDsc->hitPointsBonus );
    setHitPoints( getMaxHitPoints() );
  }
}

Monster::~Monster()
{
}

ActorFeaturePtr Monster::clone()
{
  auto* c = new Monster(*this);
  c->_damage = _damage;
  cloneBase(c);

  return ActorFeaturePtr( c );
}

bool Monster::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;
  MonsterPtr crhs = std::dynamic_pointer_cast<Monster>(rhs);

  if (crhs != nullptr)
  {
    equal = Character::isEqual( rhs );
    equal &= _damage      == crhs->_damage;
    equal &= _morale      == crhs->_morale;
  }

  return equal;
}

CarryingCapacity::LoadLevel Monster::getLoadLevel()
{
  return CarryingCapacity::LoadLevel::Light;
}

int Monster::getBaseAttackBonus()
{
  return AttackBonus::get(CharacterClassType::Monster, getLevel() );
}

int Monster::getMeleeAttackBonus()
{
  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [](Modifier& mod){ return mod.Type.generic == GenericModifier::AttackBonus; } );

  return it != _modifiers.end() ? getBaseAttackBonus() + it->Value : getBaseAttackBonus();
}

int Monster::getMissileAttackBonus()
{
  int base = getBaseAttackBonus();

  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [](Modifier& mod){ return mod.Type.generic == GenericModifier::MissileAttackBonus; } );

  return it != _modifiers.end() ? base + it->Value : base;
}

Damage Monster::getDamage()
{  
  PickablePtr weapon = getEquippedItem(ItemSlotType::MainHand);
  if ( weapon )
  {
    if ( weapon->getItemType().weapon == WeaponType::Bow ) //take missile damage
    {
      PickablePtr amunition = getEquippedItem(ItemSlotType::Amunition);
      return amunition ? amunition->getDamage() : Damage();
    }
    else
    {
      return weapon->getDamage();
    }
  }

  return _damage;
}

std::string Monster::getDescription()
{
  std::string str = Character::getDescription();

  str += colorToStr(TCODColor::darkTurquoise, true) + "Hit points dice: " + toStr( getLevel() ) + "d8" + ( _hpMod >= 0 ? "+" : "") + toStr(_hpMod);

  return str;
}

int Monster::getMorale()
{
  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [](Modifier& mod){ return mod.Type.generic == GenericModifier::MoraleModifier; } );

  return it != _modifiers.end() ? _morale + it->Value : _morale;
}

bool Monster::abilityRoll(AbilityScore::Type, int extraModifier)
{
  int roll = dices::roll(dices::D20);
  if ( roll != dices::NATURAL_ONE )
  {
    int base = roll + extraModifier + 1;
    return roll == dices::NATURAL_TWENTY || base >= AbilityScore::getAbilityRollTarget( getLevel() );
  }
  return false;
}

}

