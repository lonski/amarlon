#ifndef SKILL_H
#define SKILL_H

#include <memory>
#include <string>
#include <skill_id.h>
#include <target_type.h>
#include <target.h>
#include <skill.pb.h>

namespace amarlon {

class Skill;
class Actor;
typedef std::shared_ptr<Skill> SkillPtr;
typedef std::shared_ptr<Actor> ActorPtr;

class Skill
{
public:
  Skill(const SkillData& data);
  Skill(const Skill& skill);
  static SkillPtr create(SkillId id);

  SkillPtr clone() const;
  Skill& operator=(const Skill& skill);
  bool operator==(const Skill& rhs);

  SkillId getId() const;
  std::string getScript() const;
  int getLevel() const;
  void setLevel(int level);
  std::string getName() const;
  TargetType getTargetType() const;
  int getRadius() const;
  bool isPassive() const;
  std::string getDescription() const;

  bool use(ActorPtr user, Target target);

private:
  SkillData _data;

};

}

#endif // SKILL_H
