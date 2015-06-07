#include "character.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <actor.h>
#include <gui.h>
#include <utils.h>
#include <amarlon_except.h>
#include <map.h>
#include <destroyable.h>
#include <die_action.h>
#include <attack_bonus_table.h>

namespace amarlon {

const int NO_ARMOR_AC = 11;
const ActorFeature::Type Character::featureType = ActorFeature::CHARACTER;

Character::Character()
  : _hitPoints(0)
  , _maxHitPoints(0)
  , _level(0)
  , _experience(0)
  , _class(CharacterClass::FIGHTER)
{
}

CharacterPtr Character::create(DescriptionPtr dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  CharacterPtr character = nullptr;
  CharacterDescriptionPtr characterDsc = std::dynamic_pointer_cast<CharacterDescription>(dsc);

  if ( characterDsc != nullptr )
  {
    character.reset( new Character );
    character->_hitPoints = characterDsc->hitPoints;
    character->_maxHitPoints = characterDsc->maxHitPoints;
    character->_level = characterDsc->level;
    character->_experience = characterDsc->experience;
    character->_class = characterDsc->cClass;
    character->_abilityScores = characterDsc->abilityScores;

  }else throw creation_error("Wrong character description!");

  return character;
}

ActorFeaturePtr Character::clone()
{
  CharacterPtr cloned( new Character );

  cloned->_hitPoints = _hitPoints;
  cloned->_maxHitPoints = _maxHitPoints;
  cloned->_level = _level;
  cloned->_experience = _experience;
  cloned->_abilityScores = _abilityScores;
  cloned->_class = _class;

  return cloned;
}

bool Character::isEqual(ActorFeaturePtr rhs)
{
  bool equal = false;
  CharacterPtr crhs = std::dynamic_pointer_cast<Character>(rhs);

  if (crhs != nullptr)
  {
    equal  = _hitPoints    == crhs->_hitPoints;
    equal &= _maxHitPoints == crhs->_maxHitPoints;
    equal &= _level        == crhs->_level;
    equal &= _experience   == crhs->_experience;
    equal &= _class        == crhs->_class;
    equal &= std::equal(_abilityScores.begin(), _abilityScores.end(), crhs->_abilityScores.begin());
  }

  return equal;
}

bool Character::isAlive() const
{
  return (_hitPoints > 0);
}

int Character::getHitPoints() const
{
  return _hitPoints;
}

void Character::setHitPoints(int newHp)
{
  _hitPoints = newHp;

  if ( _hitPoints <= 0 )
  {
    ActorPtr owner = getOwner().lock();
    if ( owner )
    {
      owner->performAction( std::make_shared<DieAction>() );
    }
  }
}

void Character::modifyHitPoints(int modifier)
{
  int toSet = getHitPoints() + modifier;
  if ( toSet > getMaxHitPoints() )
  {
    toSet = getMaxHitPoints();
  }
  else if ( toSet < 0 )
  {
    toSet = 0;
  }

  setHitPoints( toSet );
}

int Character::getMaxHitPoints() const
{
  return _maxHitPoints;
}

int Character::getMeleeAttackBonus()
{
  return AttackBonusTable::getBonus(getClass(), getLevel()) + getModifier(AbilityScore::STR);
}

int Character::rollMeleeDamage()
{
  int dmg = getModifier( AbilityScore::STR );

  PickablePtr weapon = getEquippedItem(ItemSlotType::MainHand);
  if ( weapon )
  {
    dmg += dices::roll( weapon->getDamageDie() );
  }

  return dmg < 1 ? 1 : dmg; //always minimum 1 dmg inflicted
}

int Character::getArmorClass()
{
  PickablePtr armor = getEquippedItem(ItemSlotType::Armor);
  return armor ? armor->getArmorClass() : NO_ARMOR_AC;
}

int Character::getAbilityScore(AbilityScore::Type as)
{
  return _abilityScores[ as ];
}

PickablePtr Character::getEquippedItem(ItemSlotType slot)
{
  PickablePtr item;

  ActorPtr owner = getOwner().lock();
  if ( owner )
  {
    WearerPtr wearer = owner->getFeature<Wearer>();
    if ( wearer && wearer->isEquipped(slot) )
    {
      item = wearer->equipped(slot)->getFeature<Pickable>();
    }
  }

  return item;
}

int Character::getModifier(AbilityScore::Type as)
{
  return AbilityScore::getModifier( getAbilityScore(as) );
}

int Character::getExperience() const
{
  return _experience;
}

int Character::getLevel() const
{
  return _level;
}

CharacterClass Character::getClass() const
{
  return _class;
}

}
