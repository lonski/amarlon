#include "character.h"
#include <actor.h>
#include <die_action.h>
#include <utils.h>
#include <spell.h>
#include <spell_db.h>
#include <engine.h>
#include <actor_descriptions.h>
#include <spell_book.h>
#include <skill.h>
#include <algorithm>
#include <experience_table.h>
#include <rpg_db.h>
#include <race.h>
#include <character_type.h>
#include <attack_bonus_table.h>
#include <playable_character.h>

namespace amarlon {

const ActorFeature::Type Character::featureType = ActorFeature::CHARACTER;

Character::Character()  
  : Character(nullptr)
{
}

Character::~Character()
{
}

Character::Character(DescriptionPtr dsc)
  : _level(0)
  , _hitPoints(0)
  , _maxHitPoints(0)
  , _defaultArmorClass(11) //no-armor AC
  , _experience(0)
  , _speed(0)
  , _movePoints(0)
  , _spellbook(new SpellBook)
  , _team(relations::Monster)
  , _morale(0)
{
  CharacterDescriptionPtr cDsc = std::dynamic_pointer_cast<CharacterDescription>(dsc);
  if ( cDsc != nullptr )
  {
    _experience = cDsc->experience;
    _class = CharacterClass::create(cDsc->cClass);
    _race = Race::create( cDsc->race );
    _defaultArmorClass = cDsc->defaultArmorClass;
    _speed = cDsc->speed;
    _team = cDsc->team;
    _spellbook = SpellBook::create(cDsc->spellbook);
    _morale = cDsc->morale;
    _damage = cDsc->damage;

    _abilityScores = cDsc->abilityScores;
    //roll ability scores if not defined
    for ( auto as : AbilityScore::Type() )
    {
      if ( _abilityScores[as] == 0 )
      {
        MinMax constrains = _race ? _race->getAbilityScoreRestriction( as ) : MinMax();
        int roll = 0;
        while ( !constrains.allow( roll ) ) roll = dices::roll(dices::D6, 3);
        _abilityScores[as] = roll;
      }
    }

    for(auto s : cDsc->skills)
      _skills.push_back( Skill::create( static_cast<SkillId>(s.id),
                                                   s.level ) );

    setLevel( cDsc->level );
    setMaxHitPoints( cDsc->maxHitPoints );
    cDsc->hitPoints > 0 ? setHitPoints( cDsc->hitPoints ) : setHitPoints( getMaxHitPoints() );

    for(auto m : cDsc->modifiers)
      addModifier( Modifier(m) );
  }
}

CharacterPtr Character::create(DescriptionPtr dsc)
{
  CharacterPtr c;

  CharacterDescriptionPtr cDsc = std::dynamic_pointer_cast<CharacterDescription>(dsc);
  if ( cDsc )
  {
    switch (cDsc->type)
    {
      case CharacterType::Generic:            c.reset( new Character(cDsc) ); break;
      case CharacterType::PlayableCharacter:  c.reset( new PlayableCharacter(cDsc) ); break;
      default :;
    }
  }

  return c;
}

bool Character::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;
  CharacterPtr crhs = std::dynamic_pointer_cast<Character>(rhs);

  if (crhs != nullptr)
  {
    equal  = _defaultArmorClass  == crhs->_defaultArmorClass;
    equal &= _level              == crhs->_level;
    equal &= _experience         == crhs->_experience;
    equal &= _morale             == crhs->_morale;
    equal &= *_spellbook         == *(crhs->_spellbook);
    equal &= _team               == crhs->_team;
    equal &= _damage             == crhs->_damage;
    equal &= _skills.size() == crhs->_skills.size();

    equal &= _class && crhs->_class;
    if ( equal) equal &= *_class == *(crhs->_class);

    equal &= _race && crhs->_race;
    if ( equal) equal &= *_race == *(crhs->_race);

    if ( equal ) equal &= std::equal(_skills.begin(),
                                     _skills.end(),
                                     crhs->_skills.begin(),
                                     [](SkillPtr a, SkillPtr b){ return *a == *b;});

    //Ability Scores may be random per instance
    //    if ( equal ) equal &= std::equal(_abilityScores.begin(),
    //                                     _abilityScores.end(),
    //                                     crhs->_abilityScores.begin());
  }

  return equal;
}

ActorFeaturePtr Character::clone()
{
  Character* c = new Character(*this);
  cloneBase(c);
  return ActorFeaturePtr( c );
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

void Character::turnHostileTo(ActorPtr attacker)
{
  CharacterPtr attackerCh = attacker ? attacker->getFeature<Character>() : nullptr;
  if ( attackerCh && attackerCh->getTeam() == relations::Player )
  {
    setTeam(relations::PcHostileNPC);
  }
}

int Character::takeDamage(Damage dmg, ActorPtr attacker)
{
  turnHostileTo(attacker);

  //TODO: handle damage resists
  int roll = dmg.roll();

  ActorPtr actor = getOwner().lock();
  if ( actor )
  {
    if ( AiPtr ai = actor->getFeature<Ai>() ) ai->wakeUp();

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

int Character::getExperienceToNextLevel() const
{
  LevelData data = Experience::getLevelData(getClass()->getType(), getLevel() + 1);
  return data.expNeeded;
}

int Character::modifyExperience(int modifier)
{
  if ( modifier > 0 )
  {
    auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                           [](const Modifier& mod){ return mod.Type.generic == GenericModifier::ExperiencePercentBonus; } );

    if ( it != _modifiers.end() )
    {
      float bonus = modifier * (it->Value / 100.0f);
      modifier += static_cast<int>(bonus);
    }
  }

  _experience += modifier;
  return modifier;
}

int Character::getLevel() const
{
  return _level;
}

CharacterClassPtr Character::getClass() const
{
  return _class;
}

RacePtr Character::getRace() const
{
  return _race;
}

int Character::getSavingThrow(SavingThrows::Type type)
{
  int base = SavingThrows::get( type, getClass()->getType(), getLevel() );

  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [&type](Modifier& mod){ return mod.Type.savingThrow == type; } );

  return it != _modifiers.end() ? base + it->Value : base;
}

bool Character::rollSavingThrow(SavingThrows::Type type)
{
  int roll = dices::roll(dices::D20);

  if ( roll == dices::NATURAL_ONE )    return false;
  if ( roll == dices::NATURAL_TWENTY ) return true;

  return roll >= getSavingThrow(type);
}

void Character::addModifier(const Modifier &mod)
{
  auto it = std::find_if(_modifiers.begin(), _modifiers.end(), [&](Modifier& m){ return m.Type == mod.Type;});

  if ( it != _modifiers.end() )
  {
    it->Value += mod.Value;
  }
  else
  {
    _modifiers.push_back( mod );
  }
}

void Character::removeModifier(const Modifier &mod)
{
  auto it = std::find(_modifiers.begin(), _modifiers.end(), mod);

  if ( it != _modifiers.end() )
  {
    if ( it->Value == mod.Value ) _modifiers.erase( it );
    else it->Value -= mod.Value;
  }
}

relations::Team Character::getTeam() const
{
  return _team;
}

void Character::setTeam(relations::Team team)
{
  _team = team;
}

int Character::getSpeed()
{
  return std::max( _speed - calculateLoadPenalty(), 1 );
}

int Character::getMovePoints()
{
  return _movePoints;
}

void Character::setMovePoints(int points)
{
  _movePoints = points;
}

CarryingCapacity::LoadLevel Character::getLoadLevel()
{
  CarryingCapacity::Data cData = CarryingCapacity::get(getAbilityScore(AbilityScore::STR), getRace()->getType() );
  return getEquipmentWeight() >= cData.heavy ? CarryingCapacity::LoadLevel::Heavy : CarryingCapacity::LoadLevel::Light;
}

int Character::getBaseAttackBonus()
{
  int base = AttackBonus::get(getClass()->getType(), getLevel());

  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [](Modifier& mod){ return mod.Type.generic == GenericModifier::AttackBonus; } );

  return it != _modifiers.end() ? base + it->Value : base;
}

int Character::getMeleeAttackBonus()
{
  return getBaseAttackBonus() + getModifier(AbilityScore::STR);
}

int Character::getMissileAttackBonus()
{
  int base = getBaseAttackBonus() + getModifier(AbilityScore::DEX);

  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [](Modifier& mod){ return mod.Type.generic == GenericModifier::MissileAttackBonus; } );

  return it != _modifiers.end() ? base + it->Value : base;
}

Damage Character::getDamage()
{
  Damage damage = _damage;

  PickablePtr weapon = getEquippedItem(ItemSlotType::MainHand);
  if ( weapon )
  {
    if ( weapon->getItemType().weapon == WeaponType::Bow ) //take missile damage
    {
      PickablePtr amunition = getEquippedItem(ItemSlotType::Amunition);
      damage = amunition ? amunition->getDamage() : Damage();
      damage.value += getModifier( AbilityScore::DEX );
    }
    else //melee weapon
    {
      damage = weapon->getDamage();
      damage.value += getModifier( AbilityScore::STR );
    }
  }

  return damage;
}

int Character::getArmorClass(DamageType dmgType)
{
  PickablePtr armor = getEquippedItem(ItemSlotType::Armor);
  int ac = armor ? armor->getArmorClass() : _defaultArmorClass;

  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [&](Modifier& mod){ return mod.Type.ac == dmgType; } );

  return it != _modifiers.end() ? ac + it->Value : ac;
}

std::string Character::getDescription()
{
  std::string str = colorToStr(TCODColor::darkerTurquoise, true)
      + "Class: " + (getRace() == nullptr ? "" : getRace()->getName() + " ")
      + getClass()->getName() +"# #"
      + colorToStr(TCODColor::darkTurquoise, true) + "AB: +" + toStr( getBaseAttackBonus() ) + "#"
      + colorToStr(TCODColor::darkTurquoise, true) + "AC: " + toStr( getArmorClass() ) + "#";

  return str;
}

std::vector<SkillPtr> Character::getSkills() const
{
  return getSkills([](SkillPtr){return true;});
}

std::vector<SkillPtr> Character::getSkills(std::function<bool (SkillPtr)> filter) const
{
  std::vector<SkillPtr> skills;
  for ( auto s : _skills )
  {
    if ( filter(s) ) skills.push_back( getModifiedSkill(s) );
  }
  return skills;
}

SkillPtr Character::getSkill(SkillId id) const
{
  SkillPtr skill;

  for ( auto s : _skills )
  {
    if ( s->getId() == id )
    {
      skill = getModifiedSkill(s);
      break;
    }
  }

  return skill;
}

int Character::getAbilityScore(AbilityScore::Type as)
{
  return _abilityScores[ as ];
}

SkillPtr Character::getModifiedSkill(SkillPtr s) const
{
  SkillPtr skill = s->clone();

  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [&](const Modifier& mod){ return mod.Type.skill == skill->getId(); } );

  if ( it != _modifiers.end() )
  {
    skill->setLevel( skill->getLevel() + it->Value );
  }

  return skill;
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
  c->_modifiers = _modifiers;
  c->_team = _team;
  c->_morale = _morale;
  c->_abilityScores = _abilityScores;
  c->_damage = _damage;
  c->_skills.clear();
  for ( auto s : _skills ) c->_skills.push_back( s->clone() );
}


bool Character::abilityRoll(AbilityScore::Type as, int extraModifier)
{
  int roll = dices::roll(dices::D20);
  if ( roll != dices::NATURAL_ONE )
  {
    int base = roll + getModifier(as) + extraModifier;
    return  roll == dices::NATURAL_TWENTY || base >= AbilityScore::getAbilityRollTarget( getLevel() );
  }
  return false;
}

int Character::getModifier(AbilityScore::Type as)
{
  return AbilityScore::getModifier( getAbilityScore(as) );
}

int Character::getMorale()
{
  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [](Modifier& mod){ return mod.Type.generic == GenericModifier::MoraleModifier; } );

  return it != _modifiers.end() ? _morale + it->Value : _morale;
}

int Character::getEquipmentWeight()
{
  int weight = 0;

  ActorPtr owner = getOwner().lock();
  if ( owner )
  {
    weight += calculateInventoryItemsWeight();
    weight += calculateWearedItemsWeight();
  }

  return weight;
}

int Character::calculateInventoryItemsWeight()
{
  int weight = 0;

  InventoryPtr inventory = getOwner().lock()->getFeature<Inventory>();
  if ( inventory )
  {
    for ( ActorPtr i : inventory->items() )
    {
      weight += i->getFeature<Pickable>()->getWeight();
    }
  }

  return weight;
}

int Character::calculateWearedItemsWeight()
{
  int weight = 0;

  WearerPtr wearer = getOwner().lock()->getFeature<Wearer>();
  if ( wearer )
  {
    for ( auto slot : ItemSlotType() )
    {
      ActorPtr item = wearer->equipped(slot);
      if ( item )
      {
        weight = item->getFeature<Pickable>()->getWeight();
      }
    }
  }

  return weight;
}

int Character::calculateLoadPenalty()
{
  return getLoadLevel() == CarryingCapacity::LoadLevel::Heavy ? CarryingCapacity::HEAVY_LOAD_SPEED_PENALTY : 0;
}

}

