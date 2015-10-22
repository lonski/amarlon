#include "race.h"
#include <skill.h>

namespace amarlon {

Race::Race()
  : _id(RaceType::NoRace)
  , _playable(false)
{
}

RaceType Race::getType() const
{
  return _id;
}

std::string Race::getName() const
{
  return _name;
}

std::string Race::getDescription() const
{
  std::string headerColor = colorToStr(TCODColor::darkGreen, true);

  std::string dsc = headerColor + "Description:# #";

  dsc += _description;

  dsc += "# #" + headerColor + "Allowed classes:# #";
  for ( auto c : _allowedClasses )
  {
    dsc += CharacterClass2Str(c);
    dsc += "#";
  }

  if ( !_skills.empty() )
  {
    dsc += "# #" + headerColor + "Special abilities:# #";
    for ( SkillPtr s : _skills )
    {
      if ( s->getName().find("racial") == std::string::npos )
      {
        dsc += s->getName() + " (lv " + toStr(s->getLevel()) + ")";
      }
      else
      {
        dsc += "#" + s->getDescription();
      }
      dsc += "#";
    }
  }

  if ( !_abilityScoreRestrictions.empty() )
  {
    dsc += "# #" + headerColor + "Ability score restrictions:# #";
    for ( auto& pair : _abilityScoreRestrictions )
    {
      dsc += AbilityScore::toStr( pair.first ) + ": min=" + toStr(pair.second.min) + ", max=" + toStr(pair.second.max);
      dsc += "#";
    }
  }

  return dsc;
}

bool Race::isClassAllowed(CharacterClass c) const
{
  return std::find(_allowedClasses.begin(), _allowedClasses.end(), c) != _allowedClasses.end();
}

const std::vector<SkillPtr> Race::getSkills() const
{
  return _skills;
}

MinMax Race::getAbilityScoreRestriction(AbilityScore::Type as) const
{
  auto it = _abilityScoreRestrictions.find(as);
  return it != _abilityScoreRestrictions.end() ? it->second
                                               : MinMax( AbilityScore::MIN_VALUE, AbilityScore::MAX_VALUE );
}

bool Race::isPlayable() const
{
  return _playable;
}

}
