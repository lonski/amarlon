#include "character.h"
#include <playable_character.h>
#include <monster.h>
#include <actor.h>
#include <die_action.h>
#include <utils.h>

namespace amarlon {

const ActorFeature::Type Character::featureType = ActorFeature::CHARACTER;

Character::Character()  
  : _level(0)
  , _hitPoints(0)
  , _maxHitPoints(0)
  , _defaultArmorClass(11) //no-armor AC
  , _experience(0)
  , _class(CharacterClass::Monster)
  , _race(Race::NoRace)
  , _speed(0)
{
}

CharacterPtr Character::create(DescriptionPtr dsc)
{
  /* REMEBER TO UPDATE CLONE, WHEN ADDING NEW ELEMENTS */
  CharacterPtr c = nullptr;

  //playable character part
  PlayableCharacterDescriptionPtr characterDsc = std::dynamic_pointer_cast<PlayableCharacterDescription>(dsc);
  if ( characterDsc != nullptr )
  {
    PlayableCharacterPtr character( new PlayableCharacter );

    character->_hitPoints = characterDsc->hitPoints;
    character->_maxHitPoints = characterDsc->maxHitPoints;
    character->_level = characterDsc->level;
    character->_abilityScores = characterDsc->abilityScores;

    c = character;
  }
  //monster part
  else
  {
    MonsterDescriptionPtr monsterDsc = std::dynamic_pointer_cast<MonsterDescription>(dsc);
    if ( monsterDsc != nullptr )
    {
      MonsterPtr monster( new Monster(monsterDsc->level, monsterDsc->hitPointsBonus) );

      monster->_damageDice = monsterDsc->damageDice;
      monster->_damageDiceCount = monsterDsc->damageDiceCount;
      monster->_morale = monsterDsc->morale;

      c = monster;
    }
  }

  //common part
  CharacterDescriptionPtr commonDsc = std::dynamic_pointer_cast<CharacterDescription>(dsc);
  if ( commonDsc != nullptr )
  {
    c->_experience = commonDsc->experience;
    c->_class = commonDsc->cClass;
    c->_race = commonDsc->race;
    c->_defaultArmorClass = commonDsc->defaultArmorClass;
    c->_speed = commonDsc->speed;
  }

  return c;
}

bool Character::isEqual(ActorFeaturePtr rhs)
{
  bool equal = false;
  CharacterPtr crhs = std::dynamic_pointer_cast<Character>(rhs);

  if (crhs != nullptr)
  {
    equal  = _defaultArmorClass  == crhs->_defaultArmorClass;
    equal &= _level              == crhs->_level;
    //equal &= _maxHitPoints       == crhs->_maxHitPoints; this is random
    equal &= _experience         == crhs->_experience;
    equal &= _class              == crhs->_class;
    equal &= _race               == crhs->_race;
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

int Character::getMaxHitPoints() const
{
  return _maxHitPoints;
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

int Character::getExperience() const
{
  return _experience;
}

void Character::modifyExperience(int modifier)
{
  _experience += modifier;
}

int Character::getLevel() const
{
  return _level;
}

CharacterClass Character::getClass() const
{
  return _class;
}

Race Character::getRace() const
{
  return _race;
}

int Character::getSavingThrow(SavingThrows::Type type)
{
  return SavingThrows::get( type, getClass(), getLevel() );
}

int Character::getSpeed()
{
  return _speed;
}

int Character::getArmorClass()
{
  PickablePtr armor = getEquippedItem(ItemSlotType::Armor);
  return armor ? armor->getArmorClass() : _defaultArmorClass;
}

std::string Character::getDescription()
{
  std::string str = colorToStr(TCODColor::darkerTurquoise, true)
      + "Class: " + (getRace() == Race::NoRace ? "" : Race2Str(getRace()) + " ")
      + CharacterClass2Str( getClass() ) +"\n \n"
      + colorToStr(TCODColor::darkTurquoise, true) + "AB: +" + toStr( getBaseAttackBonus() ) + "\n"
      + colorToStr(TCODColor::darkTurquoise, true) + "AC: " + toStr( getArmorClass() ) + "\n";

  return str;
}

void Character::setLevel(int level)
{
  _level = level;
}

void Character::setMaxHitPoints(int maxHp)
{
  _maxHitPoints = maxHp;
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

}
