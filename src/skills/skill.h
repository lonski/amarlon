#ifndef SKILL_H
#define SKILL_H

#include <memory>
#include <string>
#include <skill_id.h>
#include <target_type.h>
#include <target.h>

namespace amarlon {

class Skill;
class Actor;
struct SkillDescription;
typedef std::shared_ptr<SkillDescription> SkillDescriptionPtr;
typedef std::shared_ptr<Skill> SkillPtr;
typedef std::shared_ptr<Actor> ActorPtr;

class Skill
{
public:
  static SkillPtr create(SkillId id, int level = 0);

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

  bool operator==(const Skill& rhs) const;
  SkillPtr clone() const;

private:
  SkillId _id;
  int _level;
  SkillDescriptionPtr _flyweight;

  Skill(SkillId id);

  friend class SkillDB;
};

}

#endif // SKILL_H
