#include "pickable.h"
#include <iostream>
#include <actor.h>
#include <gui.h>
#include <amarlon_except.h>
#include <utils.h>
#include <actor_descriptions.h>
#include <cassert>
#include <lua_state.h>
#include <engine.h>
#include <cstdio>
#include <scroll.h>
#include <module.h>

namespace amarlon {

const ActorFeature::Type Pickable::featureType = ActorFeature::PICKABLE;

void Pickable::upgrade(DescriptionPtr dsc)
{
  PickableDescriptionPtr pDsc = std::dynamic_pointer_cast<PickableDescription>(dsc);
  if ( pDsc != nullptr )
  {
    if (pDsc->stackable)  _stackable  = *(pDsc->stackable);
    if (pDsc->cursed)     _cursed  = *(pDsc->cursed);
    if (pDsc->amount)     _amount     = *(pDsc->amount);
    if (pDsc->itemSlot)   _itemSlot   = (ItemSlotType)(*pDsc->itemSlot);
    if (pDsc->armorClass) _armorClass = *(pDsc->armorClass);
    if (pDsc->weight)     _weight     = *(pDsc->weight);
    if (pDsc->price)      _price      = *(pDsc->price);
    if (pDsc->damage)     _damage     = *(pDsc->damage);
    if (pDsc->uses)       _usesCount  = *(pDsc->uses);
    if (pDsc->targetType) _targetType = (TargetType)(*pDsc->targetType);
    if (pDsc->scriptId)   _scriptId   = *(pDsc->scriptId);
    if (pDsc->range)      _range      = *(pDsc->range);
    if (pDsc->radius)     _radius     = *(pDsc->radius);
    if (pDsc->armorType)      _type.armor     = (ArmorType)*(pDsc->armorType);
    if (pDsc->weaponType)     _type.weapon    = (WeaponType)*(pDsc->weaponType);
    if (pDsc->amunitionType)  _type.amunition = (AmunitionType)*(pDsc->amunitionType);
    if (pDsc->category)       _type.category  = (PickableCategory)*(pDsc->category);
    if (pDsc->weaponSize)     _type.weaponSize  = (WeaponSize)*(pDsc->weaponSize);
    if (pDsc->useType)        _useType = (UseType)(*pDsc->useType);
    if (pDsc->useRestriction) _useRestriction = (UseRestriction)(*pDsc->useRestriction);
    if (pDsc->spellId)        _spell = Spell::create( static_cast<SpellId>(*pDsc->spellId) );
  }
}

DescriptionPtr Pickable::toDescriptionStruct(ActorFeaturePtr cmp)
{
  PickableDescriptionPtr dsc(new PickableDescription);
  PickablePtr cmpP = std::dynamic_pointer_cast<Pickable>(cmp);

  toDescriptionStruct(dsc, cmpP);

  return dsc;
}

void Pickable::toDescriptionStruct(PickableDescriptionPtr dsc, PickablePtr cmpP)
{
  if ( cmpP )
  {
    if ( _stackable != cmpP->_stackable ) dsc->stackable = _stackable;
    if ( _cursed != cmpP->_cursed ) dsc->cursed = _cursed;
    if ( _amount != cmpP->_amount ) dsc->amount = _amount;
    if ( _usesCount != cmpP->_usesCount ) dsc->uses = _usesCount;
    if ( _itemSlot != cmpP->_itemSlot )   dsc->itemSlot = (int)_itemSlot;
    if ( _armorClass != cmpP->_armorClass ) dsc->armorClass = _armorClass;
    if ( _weight != cmpP->_weight ) dsc->weight = _weight;
    if ( _price != cmpP->_price ) dsc->price = _price;
    if ( _targetType != cmpP->_targetType ) dsc->targetType = (int)_targetType;
    if ( _useType != cmpP->_useType ) dsc->useType = (int)_useType;
    if ( _useRestriction != cmpP->_useRestriction ) dsc->useType = (int)_useRestriction;
    if ( _damage != cmpP->_damage ) dsc->damage = _damage.toStr();
    if ( _scriptId != cmpP->_scriptId ) dsc->scriptId = _scriptId;
    if ( _range != cmpP->_range ) dsc->range = _range;
    if ( _radius != cmpP->_radius ) dsc->radius = _radius;
    if ( _type.armor != cmpP->_type.armor ) dsc->armorType = (int)_type.armor;
    if ( _type.weapon != cmpP->_type.weapon ) dsc->weaponType = (int)_type.weapon;
    if ( _type.amunition != cmpP->_type.amunition ) dsc->amunitionType = (int)_type.amunition;
    if ( _type.category != cmpP->_type.category ) dsc->category = (int)_type.category;
    if ( _type.weaponSize != cmpP->_type.weaponSize ) dsc->weaponSize = (int)_type.weaponSize;
    if ( (_spell && !cmpP->_spell) || (_spell && cmpP->_spell && _spell->getId() != cmpP->_spell->getId()) )
      dsc->spellId = (int)_spell->getId();
  }
  else
  {
    dsc->stackable = _stackable;
    dsc->cursed = _cursed;
    dsc->amount = _amount;
    dsc->uses = _usesCount;
    dsc->itemSlot = (int)_itemSlot;
    dsc->armorClass = _armorClass;
    dsc->weight = _weight;
    dsc->price = _price;
    dsc->targetType = (int)_targetType;
    dsc->useType = (int)_useType;
    dsc->useRestriction = (int)_useRestriction;
    dsc->damage = _damage.toStr();
    dsc->scriptId = _scriptId;
    dsc->range = _range;
    dsc->radius = _radius;
    dsc->armorType = (int)_type.armor;
    dsc->weaponType = (int)_type.weapon;
    dsc->amunitionType = (int)_type.amunition;
    dsc->category = (int)_type.category;
    dsc->weaponSize = (int)_type.weaponSize;
    if ( _spell) dsc->spellId = (int)_spell->getId();
  }
}

Pickable::Pickable(DescriptionPtr dsc)
  : _usesCount(0)
  , _stackable(false)
  , _amount(1)
  , _itemSlot(ItemSlotType::Null)
  , _armorClass(0)
  , _weight(0)
  , _price(0)
  , _targetType(TargetType::SINGLE_NEIGHBOUR)
  , _scriptId(0)
  , _range(0)
  , _radius(0)
  , _useType(UseType::FixedUses)
  , _useRestriction(UseRestriction::Null)
  , _cursed(false)
{
  upgrade(dsc);
}

Pickable::~Pickable()
{
}

PickablePtr Pickable::create(DescriptionPtr dsc)
{
  PickablePtr p;

  PickableDescriptionPtr pDsc = std::dynamic_pointer_cast<PickableDescription>(dsc);
  if ( pDsc )
  {    
    if ( pDsc->category && *pDsc->category == (int)PickableCategory::Scroll )
    {
      p.reset( new Scroll(pDsc) );
    }
    else
    {
      p.reset( new Pickable(dsc) );
    }
  }

  return p;
}

ActorPtr Pickable::spilt(int amount)
{
  ActorPtr r = ActorPtr(getOwner().lock());

  if ( isStackable() && amount < _amount && amount > 0 )
  {
    setAmount(_amount - amount);

    assert( _amount > 0 );
    assert( amount > 0 );

    r = getOwner().lock()->clone();
    r->getFeature<Pickable>()->setAmount(amount);
  }

  return r;
}

ActorFeaturePtr Pickable::clone()
{
  PickablePtr cloned( new Pickable );

  clone( cloned.get() );

  return cloned;
}

bool Pickable::isEqual(ActorFeaturePtr rhs) const
{
  bool equal = false;
  PickablePtr crhs = std::dynamic_pointer_cast<Pickable>(rhs);

  if (crhs != nullptr)
  {
    equal = (_stackable == crhs->_stackable);
    equal &= (_cursed == crhs->_cursed);
    equal &= (_armorClass == crhs->_armorClass);
    equal &= (_weight == crhs->_weight);
    equal &= (_price == crhs->_price);
    equal &= (_damage == crhs->_damage);
    equal &= (_targetType == crhs->_targetType);
    equal &= (_useType == crhs->_useType);
    equal &= (_useRestriction == crhs->_useRestriction);
    equal &= (_itemSlot == crhs->_itemSlot);
    equal &= (_scriptId == crhs->_scriptId);
    equal &= (_type == crhs->_type);
    equal &= (_radius == crhs->_radius);
    equal &= (_range == crhs->_range);
    equal &= ( ( _spell && crhs->_spell && _spell->getId() == crhs->_spell->getId() ) ||
               (!_spell && !crhs->_spell) );
  }

  return equal;
}

TargetType Pickable::getTargetType() const
{
  return _targetType;
}

int Pickable::getRange() const
{
  return _range;
}

int Pickable::getRadius() const
{
  return _radius;
}

int Pickable::getScriptId() const
{
  return _scriptId;
}

bool Pickable::use(ActorPtr executor, const Target& target)
{
  bool r = false;

  if ( isUsable() )
  {
    if ( getSpell() )
    {
      r = getSpell()->cast(executor, target) != CastResult::Nok;
    }
    else
    {
      lua_api::LuaState& lua = Engine::instance().getLuaState();

      if ( lua.execute( getScriptPath() ) )
      {
        try
        {
          r = luabind::call_function<bool>(
              lua()
            , "onUse"
            , executor
            , getOwner().lock()
            , &target
          );

        }
        catch(luabind::error& e)
        {
          lua.logError(e);
        }
      }
    }
  }

  if( r ) --_usesCount;

  return r;
}

bool Pickable::isUsable() const
{
  return _usesCount > 0 || _useType == UseType::InfiniteUse;
}

int Pickable::getUsesCount() const
{
  return _usesCount;
}

void Pickable::setUsesCount(int uses)
{
  _usesCount = uses;
}

UseType Pickable::getUseType() const
{
  return _useType;
}

void Pickable::setUseType(UseType t)
{
  _useType = t;
}

bool Pickable::isStackable() const
{
  return _stackable;
}

void Pickable::setStackable(bool stackable)
{
  _stackable = stackable;
}

ItemSlotType Pickable::getItemSlot() const
{
  return _itemSlot;
}

void Pickable::setItemSlot(const ItemSlotType &itemSlot)
{
  _itemSlot = itemSlot;
}

bool Pickable::isEquippable()
{
  return ( _itemSlot != ItemSlotType::Null );
}

PickableCategory Pickable::getCategory() const
{
  return _type.category;
}

void Pickable::setCategory(PickableCategory category)
{
  _type.category = category;
}

ItemType Pickable::getItemType() const
{
  return _type;
}

void Pickable::setItemType(ItemType type)
{
  _type = type;
}

Damage Pickable::getDamage() const
{
  return _damage;
}

Damage* Pickable::getMutableDamage()
{
  return &_damage;
}

void Pickable::setDamage(const Damage& dmg)
{
  _damage = dmg;
}

int Pickable::getArmorClass() const
{
  return _armorClass;
}

int Pickable::getWeight() const
{
  return _weight;
}

void Pickable::setWeight(int weight)
{
  _weight = weight;
}

SpellPtr Pickable::getSpell() const
{
  return _spell;
}

void Pickable::setSpell(SpellPtr spell)
{
  _spell = spell;
}

int Pickable::getPrice() const
{
  return _price;
}

std::string Pickable::getDescription()
{
  std::string str = colorToStr(TCODColor::darkerTurquoise, true) + "Category: " + PickableCategory2Str( getCategory() );

  if ( getItemSlot() != ItemSlotType::Null )
  {
    str += " (";
    str += ItemSlotType2Str( getItemSlot() ) ;
    str += ")";
  }
  str += "#";
  str += colorToStr(TCODColor::darkerTurquoise, true) + "Weight: " + toStr( getWeight() ) + " lbs# #";

  if ( getDamage() != Damage() )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Damage: ";

    if ( _damage.dice != dices::NoDice )
    {
      str += toStr(_damage.diceCount) + "d" + toStr(static_cast<int>(_damage.dice) );
    }

    if ( _damage.value != 0 )
    {
      str += ( _damage.value > 0 || isCursed() ? "+" : "-" ) + toStr(std::abs(_damage.value));
    }

    for ( auto& kv : _damage.specialDamage )
    {
      str += ( kv.second >0 ? ", +" : ", -" ) + toStr(kv.second);
      str += " vs " + std::string(SpeciesType2Str[kv.first]);
    }

    str += "#";
  }
  if ( getArmorClass() != 0 )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Armor class: " + toStr(getArmorClass()) + "#";
  }
  if ( getRange() != 0 )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Range: " + toStr(getRange()) + "#";
  }
  if ( getRadius() != 0 )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Radius: " + toStr(getRadius()) + "#";
  }

  if ( isUsable() )
  {
    str += colorToStr(TCODColor::darkTurquoise, true) + "Uses: ";
    switch ( getUseType() )
    {
      case UseType::DailyUse: str += "once per day#"; break;
      default: str += toStr(_usesCount) + "#"; break;
    }
  }

  if ( getSpell() )
  {
    str += " # #";
    str += colorToStr(TCODColor::purple, true) + "Can cast " + getSpell()->getName();

    if ( !getSpell()->getRawDescription().empty() )
    {
      str += ": # #";
      str += getSpell()->getRawDescription();
    }
  }

  return str;
}

void Pickable::tickDay()
{
  if ( getUseType() == UseType::DailyUse )
    _usesCount = 1;
}

std::string Pickable::debug(const std::string &linebreak)
{
  std::string d = " " + linebreak + "-----PICKABLE-----"+linebreak;

  d += "Stackable = " + std::string(isStackable() ? "True" : "False") + linebreak;
  d += "Amount = " + toStr(_amount) + linebreak;
  d += "Usable = " + std::string(isUsable() ? "True" : "False") + linebreak;
  d += "Uses = " + toStr(getUsesCount()) + linebreak;
  d += "UseType = " + toStr((int)getUseType()) + linebreak;
  d += "UseRestriction = " + toStr((int)getUseRestriction()) + linebreak;
  d += "Cursed = " + std::string(isCursed() ? "True" : "False") + linebreak;

  d += "----------------" + linebreak;

  return d;
}

void Pickable::clone(Pickable *p)
{
  if ( p )
  {
    p->_stackable = _stackable;
    p->_cursed = _cursed;
    p->_amount = _amount;
    p->_itemSlot = _itemSlot;
    p->_damage = _damage;
    p->_armorClass = _armorClass;
    p->_weight = _weight;
    p->_price = _price;
    p->_usesCount = _usesCount;
    p->_targetType = _targetType;
    p->_useType = _useType;
    p->_useRestriction = _useRestriction;
    p->_itemSlot = _itemSlot;
    p->_scriptId = _scriptId;
    p->_type = _type;
    p->_range = _range;
    p->_radius = _radius;
    if ( _spell) p->_spell = _spell->clone();
  }
}

bool Pickable::isCursed() const
{
  return _cursed;
}

void Pickable::setCursed(bool cursed)
{
  _cursed = cursed;
}

UseRestriction Pickable::getUseRestriction() const
{
  return _useRestriction;
}

void Pickable::setUseRestriction(UseRestriction useRestriction)
{
  _useRestriction = useRestriction;
}

std::string Pickable::getScriptPath() const
{
  std::string default_script = "scripts/items/" + std::to_string( static_cast<int>(_scriptId) ) + ".lua";
  std::string module_script = Engine::instance().getModule().getPath() + default_script;

  return file_exists(module_script) ? module_script : default_script;
}

int Pickable::getAmount() const
{
  return _amount;
}

void Pickable::setAmount(int amount)
{
  _amount = amount;
}

}

