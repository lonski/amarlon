#include "character.h"
#include <actor.h>
#include <die_action.h>
#include <utils.h>
#include <character_factory.h>
#include <spell.h>
#include <spell_gateway.h>
#include <engine.h>
#include <actor_descriptions.h>

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
  , _movePoints(0)
{
}

CharacterPtr Character::create(DescriptionPtr dsc)
{
  static CharacterFactory factory;
  return factory.produce( std::dynamic_pointer_cast<CharacterDescription>(dsc) );
}

bool Character::isEqual(ActorFeaturePtr rhs) const
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
    equal &= _spells             == crhs->_spells;
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

int Character::takeDamage(Damage dmg, ActorPtr attacker)
{
  //TODO: handle damage resists
  int roll = dmg.roll();

  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    if ( attacker )
      actor->notify(Event(EventId::Actor_GotHit,
                    { {"attacker", attacker->getName()}, {"value", std::to_string(roll)} } ));
    else
      actor->notify(Event(EventId::Actor_ReceivedDamage,
                    { {"value", std::to_string(roll)} } ));
  }

  modifyHitPoints(-1 * roll);
  return roll;
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

int Character::getMovePoints()
{
  return _movePoints;
}

void Character::setMovePoints(int points)
{
  _movePoints = points;
}

int Character::getArmorClass()
{
  PickablePtr armor = getEquippedItem(ItemSlotType::Armor);
  return armor ? armor->getArmorClass() : _defaultArmorClass;
}

std::vector<SpellPtr> Character::getSpells() const
{
  return std::vector<SpellPtr>{_spells.begin(), _spells.end()};
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

void Character::Creator::fillCommonCharacterPart(CharacterPtr character, CharacterDescriptionPtr dsc)
{
  if ( character != nullptr && dsc != nullptr )
  {
    character->_experience = dsc->experience;
    character->_class = dsc->cClass;
    character->_race = dsc->race;
    character->_defaultArmorClass = dsc->defaultArmorClass;
    character->_speed = dsc->speed;
    for(auto id : dsc->spells )
    {
      character->_spells.insert( Engine::instance().getSpellGateway().fetch(id) );
    }
  }
}

}
