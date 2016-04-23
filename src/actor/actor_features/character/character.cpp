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
  , _baseArmorClass(11) //no-armor AC
  , _experience(0)
  , _speed(0)
  , _movePoints(0)
  , _spellbook(new SpellBook)
  , _team(relations::Monster)
  , _morale(0)
  , _species(SpeciesType::Null)
{
  upgrade(dsc);

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
}

void Character::upgrade(DescriptionPtr dsc)
{
  CharacterDescriptionPtr cDsc = std::dynamic_pointer_cast<CharacterDescription>(dsc);
  if ( cDsc != nullptr )
  {
    if ( cDsc->experience)         _experience = *cDsc->experience;
    if ( cDsc->cClass )
      _class = CharacterClass::create( static_cast<CharacterClassType>(*cDsc->cClass) );
    if ( cDsc->race )
      _race = Race::create( static_cast<RaceType>(*cDsc->race) );
    if ( cDsc->defaultArmorClass ) _baseArmorClass = *cDsc->defaultArmorClass;
    if ( cDsc->speed )             _speed = *cDsc->speed;
    if ( cDsc->team )              _team = static_cast<relations::Team>(*cDsc->team);
    if ( cDsc->spellbook)          _spellbook = SpellBook::create(*cDsc->spellbook);
    if ( cDsc->morale)             _morale = *cDsc->morale;
    if ( cDsc->damage)             _damage = *cDsc->damage;
    if ( cDsc->level )             _level = *cDsc->level;
    if ( cDsc->maxHitPoints )      _maxHitPoints = *cDsc->maxHitPoints;
    if ( cDsc->hitPoints )         _hitPoints = *cDsc->hitPoints; else setHitPoints( getMaxHitPoints() );
    if ( cDsc->species )           _species = static_cast<SpeciesType>(*cDsc->species);

    //upgrade the ability scores
    for ( auto kv : cDsc->abilityScores )
    {
      _abilityScores[ static_cast<AbilityScore::Type>(kv.first) ] = kv.second;
    }

    //upgrade skills
    for(auto s : cDsc->skills)
    {
      SkillPtr skill = Skill::create( static_cast<SkillId>(s.first), s.second );

      //remove if already exists
      auto it = std::find_if(_skills.begin(), _skills.end(), [&](SkillPtr sk){
        return sk->getId() == skill->getId();
      });
      if ( it != _skills.end() ) _skills.erase(it);

      //insert the skill
      _skills.push_back( skill );
    }

    //add modifiers
    for(auto m : cDsc->modifiers)
      addModifier( Modifier(m) );
  }
}

DescriptionPtr Character::toDescriptionStruct(ActorFeaturePtr cmp)
{
  CharacterDescriptionPtr dsc;
  CharacterPtr cmpChr = std::dynamic_pointer_cast<Character>(cmp);

  dsc.reset( new CharacterDescription );
  toDescriptionStruct( dsc, cmpChr );

  return dsc;
}

void Character::toDescriptionStruct(CharacterDescriptionPtr dsc, CharacterPtr cmp)
{
  if ( dsc )
  {
    if ( cmp )
    {
      if ( cmp->_level != _level ) dsc->level = _level;
      if ( cmp->_hitPoints != _hitPoints ) dsc->hitPoints = _hitPoints;
      if ( cmp->_maxHitPoints != _maxHitPoints ) dsc->maxHitPoints = _maxHitPoints;
      if ( cmp->_baseArmorClass != _baseArmorClass ) dsc->defaultArmorClass = _baseArmorClass;
      if ( cmp->_experience != _experience ) dsc->experience = _experience;
      if (_class) dsc->cClass = static_cast<int>(_class->getType());
      if (_race) dsc->race = static_cast<int>(_race->getType());
      if ( cmp->_speed != _speed ) dsc->speed = _speed;
      if ( cmp->_team != _team ) dsc->team = static_cast<int>(_team);
      if ( cmp->_morale != _morale ) dsc->morale = _morale;
      if ( cmp->_damage != _damage ) dsc->damage = _damage.toStr();
      if ( cmp->_spellbook != _spellbook ) dsc->spellbook = *_spellbook->toDescriptionStruct();
      if ( cmp->_species != _species ) dsc->species = static_cast<int>(_species);

      for (Modifier& mod : _modifiers)
        dsc->modifiers.push_back( mod.toString() );

      for ( auto& kv : _abilityScores )
        if ( cmp->_abilityScores[kv.first] != _abilityScores[kv.first] )
          dsc->abilityScores[ (int)kv.first ] = kv.second;

      for ( SkillPtr sk : _skills )
        dsc->skills.push_back( std::make_pair((int)sk->getId(), sk->getLevel()) );

      dsc->type = static_cast<int>(CharacterType::Generic);
    }
    else
    {
      dsc->level = _level;
      dsc->hitPoints = _hitPoints;
      dsc->maxHitPoints = _maxHitPoints;
      dsc->defaultArmorClass = _baseArmorClass;
      dsc->experience = _experience;
      dsc->cClass = static_cast<int>(_class->getType());
      dsc->race = static_cast<int>(_race->getType());
      dsc->speed = _speed;
      dsc->type = static_cast<int>(CharacterType::Generic);
      dsc->team = static_cast<int>(_team);
      dsc->morale = _morale;
      dsc->damage = _damage.toStr();
      dsc->spellbook = *_spellbook->toDescriptionStruct();
      dsc->species = static_cast<int>(_species);

      for (Modifier& mod : _modifiers)
        dsc->modifiers.push_back( mod.toString() );

      for ( auto& kv : _abilityScores )
        dsc->abilityScores[ (int)kv.first ] = kv.second;

      for ( SkillPtr sk : _skills )
        dsc->skills.push_back( std::make_pair((int)sk->getId(), sk->getLevel()) );

    }
  }
}

CharacterPtr Character::create(DescriptionPtr dsc)
{
  CharacterPtr c;

  CharacterDescriptionPtr cDsc = std::dynamic_pointer_cast<CharacterDescription>(dsc);
  if ( cDsc && cDsc->type )
  {
    switch ( (CharacterType)*cDsc->type)
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
    equal  = _baseArmorClass  == crhs->_baseArmorClass;
    equal &= _level              == crhs->_level;
    equal &= _experience         == crhs->_experience;
    equal &= _morale             == crhs->_morale;
    equal &= *_spellbook         == *(crhs->_spellbook);
    equal &= _team               == crhs->_team;
    equal &= _damage             == crhs->_damage;
    equal &= _skills.size() == crhs->_skills.size();
    equal &= _species            == crhs->_species;

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
  int healed = modifyHitPoints(heal.roll(getSpecies()));

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

std::string Character::debug(const std::string& linebreak = "\n")
{
  std::string d = " " + linebreak + "-----CHARACTER-----"+linebreak;

  d += "Level = " + toStr(_level) + linebreak;
  d += "HP = " + toStr(_hitPoints) + "/" + toStr(_maxHitPoints)  + linebreak;
  d += "Base AC = " + toStr(_baseArmorClass)  + linebreak;
  d += "AC (Physical) = " + toStr(getArmorClass())  + linebreak;
  d += "Experience = " + toStr(_experience)  + linebreak;
  d += "Speed = " + toStr(getSpeed())  + linebreak;
  d += "Team = " + toStr((int)_team)  + linebreak;
  d += "Species = " + toStr((int)_species)  + linebreak;
  d += "Morale = " + toStr(_morale)  + linebreak;
  d += "Bare hands damage = " + _damage.toStr(true)  + linebreak;
  d += "Damage = " + getDamage().toStr(true)  + linebreak;
  d += " >>> Ability Scores" + linebreak;
  for ( auto& kv : _abilityScores )
  {
    d += AbilityScore::toStr(kv.first) + " = " + toStr(kv.second)  + linebreak;
  }
  d += " >>> Skills" + linebreak;
  for ( SkillPtr skill : _skills )
  {
    d+= "Skill " + skill->getName() + "ID=" + toStr( (int)skill->getId() ) + " Level=" + toStr(skill->getLevel()) + linebreak;
  }
  d += "----------------" + linebreak;

  return d;
}

int Character::takeDamage(Damage dmg, ActorPtr attacker)
{
  turnHostileTo(attacker);

  //TODO: handle damage resists
  int roll = dmg.roll(getSpecies());

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
    if ( weapon->getItemType().isRangeWeapon() ) //take missile damage
    {
      PickablePtr amunition = getEquippedItem(ItemSlotType::Amunition);
      damage = amunition ? amunition->getDamage() : Damage();
      damage.value += getModifier( AbilityScore::DEX );
      damage += weapon->getDamage();
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
  int ac = _baseArmorClass + accumulateEquippedItemsAC();

  auto it = std::find_if(_modifiers.begin(), _modifiers.end(),
                         [&](Modifier& mod){ return mod.Type.ac == dmgType; } );

  return it != _modifiers.end() ? ac + it->Value : ac;
}

int Character::accumulateEquippedItemsAC()
{
  int ac = 0;

  if ( ActorPtr owner = getOwner().lock() )
  {
    if ( WearerPtr wearer = owner->getFeature<Wearer>() )
    {
      for ( ItemSlotType slot : ItemSlotType() )
      {
        if ( ActorPtr eq = wearer->equipped(slot) )
        {
          if ( PickablePtr item = eq->getFeature<Pickable>() )
          {
            ac += item->getArmorClass();
          }
        }
      }
    }
  }

  return ac;
}

SpeciesType Character::getSpecies() const
{
  return _species;
}

void Character::setSpecies(const SpeciesType &species)
{
  _species = species;
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
  c->_species = _species;
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

