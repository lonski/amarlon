#include "monster.h"
#include <actor.h>
#include <die_action.h>
#include <attack_bonus_table.h>
#include <iostream>
#include <utils.h>
#include <actor_descriptions.h>
#include <race.h>

namespace amarlon {

Monster::Monster(int level, int hitPointsBonus)
  : _morale(0)
  , _hpMod(hitPointsBonus)
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
  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [](Modifier& mod){ return mod.Type.generic == GenericModifier::MoraleModifier; } );

  return it != _modifiers.end() ? _morale + it->Value : _morale;
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

