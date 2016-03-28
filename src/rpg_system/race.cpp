#include "race.h"
#include <skill.h>
#include <engine.h>
#include <rpg_db.h>
#include <race_description.h>

namespace amarlon {

Race::Race()
  : _id(RaceType::NoRace)
  , _playable(false)
{
}

RacePtr Race::create(RaceType id)
{
  return Engine::instance().getRpgDB().getRace(id);
}

RacePtr Race::create(RaceDescriptionPtr dsc)
{
  RacePtr race;
  if ( dsc  )
  {
    race.reset( new Race );
    race->_id = static_cast<RaceType>(dsc->id);
    race->_name = dsc->name;
    race->_description = dsc->description;
    race->_playable = dsc->playable;

    for ( auto ac : dsc->possibleClasses )
      race->_allowedClasses.push_back(
            static_cast<CharacterClassType>(ac) );

    for ( auto ps : dsc->skills )
    {
      SkillPtr skill = Skill::create(static_cast<SkillId>(ps.first));
      skill->setLevel(ps.second);
      race->_skills.push_back( skill );
    }

    for ( auto asr : dsc->abilityScoreRestrictions )
      race->_abilityScoreRestrictions[ static_cast<AbilityScore::Type>(asr.first) ]
          = asr.second;
  }
  return race;
}

RacePtr Race::clone() const
{
  RacePtr cloned(new Race);

  cloned->_id = _id;
  cloned->_name = _name;
  cloned->_description = _description;
  cloned->_playable = _playable;
  cloned->_abilityScoreRestrictions = _abilityScoreRestrictions;
  cloned->_allowedClasses = _allowedClasses;
  for(auto s : _skills) cloned->_skills.push_back( s->clone() );

  return cloned;
}

bool Race::operator==(const Race &rhs) const
{
  return _id == rhs.getType();
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

  return dsc;
}

bool Race::isClassAllowed(CharacterClassType c) const
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
