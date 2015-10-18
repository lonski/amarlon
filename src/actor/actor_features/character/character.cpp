#include "character.h"
#include <actor.h>
#include <die_action.h>
#include <utils.h>
#include <character_factory.h>
#include <spell.h>
#include <spell_db.h>
#include <engine.h>
#include <actor_descriptions.h>
#include <spell_book.h>
#include <skill.h>

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
  , _abTempBonus(0)
  , _spellbook(new SpellBook)
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
    equal &= *_spellbook         == *(crhs->_spellbook);
    equal &= _skills.size() == crhs->_skills.size();

    if ( equal ) equal &= std::equal(_skills.begin(),
                                     _skills.end(),
                                     crhs->_skills.begin(),
                                     [](SkillPtr a, SkillPtr b){ return *a == *b;});
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
}

int Character::modifyHitPoints(int modifier)
{
  int hpBeforeHeal = getHitPoints();
  int toSet = hpBeforeHeal + modifier;
  if ( toSet > getMaxHitPoints() )
  {
    toSet = getMaxHitPoints();
  }
  else if ( toSet < 0 )
  {
    toSet = 0;
  }

  setHitPoints( toSet );
  return getHitPoints() - hpBeforeHeal;
}

int Character::takeHeal(Damage heal, ActorPtr healer)
{
  int healed = modifyHitPoints(heal.roll());

  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    if ( healer && healer != actor )
      actor->notify(Event(EventId::Actor_Healed,
                    { {"healer", healer->getName()}, {"value", std::to_string(healed)} } ));
    else
      actor->notify(Event(EventId::Actor_Healed,
                    { {"value", std::to_string(healed)} } ));
  }

  return healed;
}

int Character::takeDamage(Damage dmg, ActorPtr attacker)
{
  //TODO: handle damage resists
  int roll = dmg.roll();

  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    actor->wakeUp();

    if ( attacker )
      actor->notify(Event(EventId::Actor_GotHit,
                    { {"attacker", attacker->getName()}, {"value", std::to_string(roll)} } ));
    else
      actor->notify(Event(EventId::Actor_ReceivedDamage,
                    { {"value", std::to_string(roll)} } ));
  }

  modifyHitPoints(-1 * roll);

  //Die
  if ( _hitPoints <= 0 && actor )
  {
    actor->performAction( std::make_shared<DieAction>() );
    if ( attacker )
    {
      if ( CharacterPtr c = attacker->getFeature<Character>() )
      {
        c->modifyExperience( getExperience() );
      }
    }
  }

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
  return SavingThrows::get( type, getClass(), getLevel() ) + getTmpSavingThrowModifier(type);
}

bool Character::rollSavingThrow(SavingThrows::Type type)
{
  int roll = dices::roll(dices::D20);

  if ( roll == dices::NATURAL_ONE )    return false;
  if ( roll == dices::NATURAL_TWENTY ) return true;

  return roll >= getSavingThrow(type);
}

int Character::getTmpSavingThrowModifier(SavingThrows::Type type)
{
  return _savingThrowsTmpMods[type];
}

void Character::setTmpSavingThrowModifier(SavingThrows::Type type, int modifier)
{
  _savingThrowsTmpMods[type] = modifier;
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

int Character::getTmpAttackModifier()
{
  return _abTempBonus;
}

void Character::setTmpAttackModifier(int bonus)
{
  _abTempBonus = bonus;
}

int Character::getTmpArmorClassModifier(DamageType dmgType)
{
  return _acTempBonus[dmgType];
}

void Character::setTmpArmorClassModifier(int bonus, DamageType dmgType)
{
  _acTempBonus[dmgType] = bonus;
}

int Character::getArmorClass(DamageType dmgType)
{
  PickablePtr armor = getEquippedItem(ItemSlotType::Armor);
  int ac = armor ? armor->getArmorClass() : _defaultArmorClass;

  return ac + getTmpArmorClassModifier(dmgType);
}

std::string Character::getDescription()
{
  std::string str = colorToStr(TCODColor::darkerTurquoise, true)
      + "Class: " + (getRace() == Race::NoRace ? "" : Race2Str(getRace()) + " ")
      + CharacterClass2Str( getClass() ) +"# #"
      + colorToStr(TCODColor::darkTurquoise, true) + "AB: +" + toStr( getBaseAttackBonus() ) + "#"
      + colorToStr(TCODColor::darkTurquoise, true) + "AC: " + toStr( getArmorClass() ) + "#";

  return str;
}

std::vector<SkillPtr> Character::getSkills() const
{
  return _skills;
}

void Character::rest()
{
  setHitPoints( getMaxHitPoints() );
  _spellbook->prepareSpells();
}

SpellBookPtr Character::getSpellBook()
{
  return _spellbook;
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

void Character::cloneBase(Character *c)
{
  c->_spellbook = _spellbook->clone();
  c->_skills.clear();
  for ( auto s : _skills ) c->_skills.push_back( s->clone() );
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
    character->_spellbook = SpellBook::create(dsc->spellbook);
    for(auto s : dsc->skills)
      character->_skills.push_back( Skill::create( static_cast<SkillId>(s.id),
                                                   s.level ) );
  }
}

}

