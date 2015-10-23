#include "character_class.h"
#include <engine.h>
#include <rpg_db.h>

namespace amarlon {

CharacterClass::CharacterClass()
  : _id(CharacterClassType::NoClass)
  , _playable(false)
{
}

CharacterClassPtr CharacterClass::create(CharacterClassType type)
{
  return Engine::instance().getRpgDB().getCharacterClass(type);
}

CharacterClassPtr CharacterClass::clone() const
{
  CharacterClassPtr c(new CharacterClass);

  c->_id = _id;
  c->_name = _name;
  c->_description = _description;
  c->_playable = _playable;
  c->_abilityScoreRestrictions = _abilityScoreRestrictions;
  c->_itemTypeRestrictions = _itemTypeRestrictions;

  return c;
}

bool CharacterClass::operator==(const CharacterClass &rhs) const
{
  return _id == rhs.getType();
}

CharacterClassType CharacterClass::getType() const
{
  return _id;
}

std::string CharacterClass::getName() const
{
  return _name;
}

std::string CharacterClass::getDescription() const
{
  std::string headerColor = colorToStr(TCODColor::darkGreen, true);

  std::string dsc = headerColor + "Description:# #";

  dsc += _description;

  if ( !_abilityScoreRestrictions.empty() )
  {
    dsc += "# #" + headerColor + "Ability score restrictions:# #";
    for ( auto& pair : _abilityScoreRestrictions )
    {
      dsc += AbilityScore::toStr( pair.first ) + ": ";
      if ( pair.second.min != AbilityScore::MIN_VALUE )
      {
        dsc += "min=" + toStr(pair.second.min);
      }
      if ( pair.second.max != AbilityScore::MAX_VALUE )
      {
        dsc += "max=" + toStr(pair.second.max);
      }

      dsc += "#";
    }
  }

  if ( !_itemTypeRestrictions.empty() )
  {
    dsc += "# #" + headerColor + "Can use only:# #";
    for (auto r : _itemTypeRestrictions )
    {
      dsc += r.toString() + "#";
    }
  }

  return dsc;
}

bool CharacterClass::isPlayable() const
{
  return _playable;
}

const std::vector<ItemTypeRestriction> CharacterClass::getItemRestrictions() const
{
  return _itemTypeRestrictions;
}

bool CharacterClass::isItemAllowed(ItemType itemType)
{
  bool allowed = true;

  if ( !_itemTypeRestrictions.empty() )
    for(auto r : _itemTypeRestrictions)
      allowed &= r.allow(itemType);

  return allowed;
}

MinMax CharacterClass::getAbilityScoreRestriction(AbilityScore::Type as) const
{
  auto it = _abilityScoreRestrictions.find(as);
  return it != _abilityScoreRestrictions.end() ? it->second
                                               : MinMax( AbilityScore::MIN_VALUE, AbilityScore::MAX_VALUE );
}

}
