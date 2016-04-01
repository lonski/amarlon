#include "character.h"
#include <actor.h>
#include <die_action.h>
#include <utils.h>
#include <spell.h>
#include <spell_db.h>
#include <engine.h>

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

const ActorFeature::Type Character::FeatureType = ActorFeature::CHARACTER;

CharacterPtr Character::create(const CharacterData& data)
{
  CharacterPtr c;

  switch ( static_cast<CharacterType>(data.charactertype()) )
  {
    case CharacterType::Generic:            c.reset( new Character(data) ); break;
    case CharacterType::PlayableCharacter:  c.reset( new PlayableCharacter(data) ); break;
    default :;
  }

  return c;
}

Character::Character()
  : _spellbook( new SpellBook )
{
}

Character::Character(const Character &rhs)
{
  *this = rhs;
}

Character::~Character()
{
}

bool Character::operator==(const Character &rhs) const
{
  rhs.updateData();
  updateData();
  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

Character &Character::operator=(const Character& rhs)
{
  if ( this != &rhs )
  {
    rhs.updateData();
    _data.CopyFrom(rhs._data);
    initialize();
  }
  return *this;
}

Character::Character(const CharacterData &data)
{
  _data.CopyFrom(data);
  initialize();
}

void Character::initialize()
{
  //Set default no-armor AC
  if ( _data.baseac() == 0 ) _data.set_baseac(11);

  //roll ability scores if not defined
  for ( auto as : AbilityScore::Type() )
  {
    if ( getAbilityScore(as) == 0 )
    {
      RacePtr race = getRace();
      MinMax constrains = race ? race->getAbilityScoreRestriction( as ) : MinMax();
      int roll = 0;
      while ( !constrains.allow( roll ) ) roll = dices::roll(dices::D6, 3);
      setAbilityScore(as, roll);
    }
  }

  //initialize spellbook
  _spellbook.reset( new SpellBook(_data.spellbook()) );

  //initialize skills
  _skills.clear();
  for(auto sIt = _data.skills().begin(); sIt != _data.skills().end(); ++sIt )
  {
    SkillPtr skill = Skill::create( static_cast<SkillId>(sIt->first()) );
    skill->setLevel( sIt->second() );
    _skills.push_back( skill );
  }

  //initialize modifiers
  for(auto mIt = _data.modifiers().begin(); mIt != _data.modifiers().end(); ++mIt)
    addModifier( Modifier(*mIt) );

}

const CharacterData& Character::getData() const
{
  updateData();
  return _data;
}

const google::protobuf::Message& Character::getDataPolymorphic() const
{
  return getData();
}

ActorFeature::Type Character::getFeatureType()
{
  return Character::FeatureType;
}

void Character::updateData() const
{
  //update spellbook
  _data.mutable_spellbook()->CopyFrom( _spellbook->getData() );

  //update modifiers
  auto* modifiersData = _data.mutable_modifiers();
  modifiersData->Clear();
  for ( auto m : _modifiers )
    *(modifiersData->Add()) = m.toString();

  //update skills
  auto* skillsData = _data.mutable_skills();
  skillsData->Clear();
  for ( auto s : _skills )
  {
    auto* entry = skillsData->Add();
    entry->set_first( static_cast<int>(s->getId()) );
    entry->set_second( s->getLevel() );
  }
}

bool Character::isAlive() const
{
  return ( _data.hp() > 0);
}

int Character::getHitPoints() const
{
  return _data.hp();
}

int Character::getMaxHitPoints() const
{
  return _data.maxhp();
}

void Character::setHitPoints(int newHp)
{
  _data.set_hp(newHp);
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

std::string Character::debug(const std::string& linebreak = "\n")
{
  std::string d = " " + linebreak + "-----CHARACTER-----"+linebreak;

  d += "Level = " + toStr( _data.level() ) + linebreak;
  d += "HP = " + toStr( _data.hp() ) + "/" + toStr(_data.maxhp())  + linebreak;
  d += "Base AC = " + toStr( _data.baseac() )  + linebreak;
  d += "Experience = " + toStr( _data.experience() )  + linebreak;
  d += "Speed = " + toStr(getSpeed())  + linebreak;
  d += "Team = " + toStr(_data.team())  + linebreak;
  d += "Morale = " + toStr(_data.morale())  + linebreak;
  d += "Bare hands damage = " + getBareHandsDamage().toStr(true)  + linebreak;
  d += "Damage = " + getDamage().toStr(true)  + linebreak;
  d += " >>> Ability Scores" + linebreak;

  for ( auto as : AbilityScore::Type() )
  {
    d += AbilityScore::toStr(as) + " = " + toStr( getAbilityScore(as) )  + linebreak;
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
  if ( _data.hp() <= 0 && actor )
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
  return _data.experience();
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

  _data.set_experience( _data.experience() + modifier );
  return modifier;
}

int Character::getLevel() const
{
  return _data.level();
}

CharacterClassPtr Character::getClass() const
{
  return CharacterClass::create( static_cast<CharacterClassType>(_data.classtype()) );
}

RacePtr Character::getRace() const
{
  return Race::create( static_cast<RaceType>(_data.racetype()) );
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
  return static_cast<relations::Team>(_data.team());
}

void Character::setTeam(relations::Team team)
{
  _data.set_team( static_cast<int>(team) );
}

int Character::getSpeed()
{
  return std::max( _data.speed() - calculateLoadPenalty(), 1 );
}

int Character::getMovePoints()
{
  return _data.movepoints();
}

void Character::setMovePoints(int points)
{
  _data.set_movepoints(points);
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

Damage Character::getBareHandsDamage()
{
  return Damage(_data.damage());
}

Damage Character::getDamage()
{
  Damage damage = getBareHandsDamage();

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
  int ac = armor ? armor->getArmorClass() : _data.baseac();

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
  for ( auto it = _data.abilityscores().begin(); it != _data.abilityscores().end(); ++it )
    if ( it->first() == static_cast<int>(as) ) return it->second();

  return 0;
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
  _data.set_level(level);
}

void Character::setMaxHitPoints(int maxHp)
{
  _data.set_maxhp(maxHp);
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

void Character::setAbilityScore(AbilityScore::Type as, int value)
{
  for ( auto it = _data.mutable_abilityscores()->begin(); it != _data.mutable_abilityscores()->end(); ++it )
    if ( it->first() == static_cast<int>(as) ) it->set_second(value);
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

  return it != _modifiers.end() ? _data.morale() + it->Value : _data.morale();
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

