#include "monster.h"
#include <actor.h>
#include <die_action.h>
#include <attack_bonus_table.h>
#include <iostream>
#include <utils.h>
#include <actor_descriptions.h>

namespace amarlon {

Monster::Monster(int level, int hitPointsBonus)
  : _morale(0)
  , _hpMod(hitPointsBonus)
  , _tmpMoraleModifier(0)
{
  setLevel(level);
  setMaxHitPoints( std::max( dices::roll(dices::D8, getLevel() ) + _hpMod, 1 ) );
  setHitPoints( getMaxHitPoints() );
}

Monster::~Monster()
{
}

ActorFeaturePtr Monster::clone()
{
  return ActorFeaturePtr( new Monster(*this) );
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
  return getMeleeAttackBonus();
}

int Monster::getMeleeAttackBonus()
{
  return AttackBonus::get(CharacterClass::Monster, getLevel() );
}

Damage Monster::getDamage()
{  
  PickablePtr weapon = getEquippedItem(ItemSlotType::MainHand);
  if ( weapon )
  {
    return weapon->getDamage();
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
  return _morale + _tmpMoraleModifier;
}

int Monster::getTmpMoraleModifier()
{
  return _tmpMoraleModifier;
}

void Monster::setTmpMoraleModifier(int modifier)
{
  _tmpMoraleModifier = modifier;
}

CharacterPtr Monster::Creator::create(CharacterDescriptionPtr dsc)
{
  MonsterPtr mob = nullptr;

  MonsterDescriptionPtr mobDsc = std::dynamic_pointer_cast<MonsterDescription>(dsc);
  if ( mobDsc != nullptr )
  {
    mob = std::make_shared<Monster>(mobDsc->level, mobDsc->hitPointsBonus);

    mob->_damage = mobDsc->damage;
    mob->_morale = mobDsc->morale;

    Character::Creator::fillCommonCharacterPart(mob, dsc);
  }

  return mob;
}

}

