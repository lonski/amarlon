#ifndef RACE_H
#define RACE_H

#include <vector>
#include <string>
#include <map>
#include <character_classes.h>
#include <races.h>
#include <skill_id.h>
#include <ability_scores.h>
#include <utils.h>

namespace amarlon {

class Skill;
typedef std::shared_ptr<Skill> SkillPtr;

class Race
{
public:
  Race();

  RaceType getType() const;
  std::string getName() const;
  std::string getDescription() const;
  bool isClassAllowed(CharacterClass c) const;
  const std::vector<SkillPtr> getSkills() const;
  MinMax getAbilityScoreRestriction(AbilityScore::Type as) const;
  bool isPlayable() const;

private:
  RaceType _id;
  std::string _name;
  std::string _description;
  bool _playable;
  std::vector<CharacterClass> _allowedClasses;
  std::vector<SkillPtr> _skills;
  std::map<AbilityScore::Type, MinMax> _abilityScoreRestrictions;

  friend class RpgParser;

};

typedef std::shared_ptr<Race> RacePtr;

}

#endif // RACE_H
