#ifndef RACE_H
#define RACE_H

#include <vector>
#include <string>
#include <map>
#include <character_class_type.h>
#include <race_type.h>
#include <skill_id.h>
#include <ability_scores.h>
#include <utils.h>

namespace amarlon {

class Skill;
class Race;
struct RaceDescription;
typedef std::shared_ptr<RaceDescription> RaceDescriptionPtr;
typedef std::shared_ptr<Race> RacePtr;
typedef std::shared_ptr<Skill> SkillPtr;

class Race
{
public:
  Race();
  static RacePtr create(RaceType id);
  static RacePtr create(RaceDescriptionPtr dsc);
  RacePtr clone() const;
  bool operator==(const Race& rhs) const;

  RaceType getType() const;
  std::string getName() const;
  std::string getDescription() const;
  bool isClassAllowed(CharacterClassType c) const;
  const std::vector<SkillPtr> getSkills() const;
  MinMax getAbilityScoreRestriction(AbilityScore::Type as) const;
  bool isPlayable() const;

private:
  RaceType _id;
  std::string _name;
  std::string _description;
  bool _playable;
  std::vector<CharacterClassType> _allowedClasses;
  std::vector<SkillPtr> _skills;
  std::map<AbilityScore::Type, MinMax> _abilityScoreRestrictions;

  friend class RpgParser;

};


}

#endif // RACE_H
