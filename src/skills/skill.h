#ifndef SKILL_H
#define SKILL_H

#include <memory>
#include <string>
#include <skill_id.h>
#include <target.h>

namespace amarlon {

class Skill;
class Actor;
typedef std::shared_ptr<Skill> SkillPtr;
typedef std::shared_ptr<Actor> ActorPtr;

class Skill
{
public:
  static SkillPtr create(SkillId id, int level = 0);

  SkillId getId() const;
  std::string getScript() const;
  int getLevel() const;
  std::string getName() const;

  bool use(ActorPtr user, Target target);

private:
  SkillId _id;
  int _level;

  Skill(SkillId id, int level);

};

}

#endif // SKILL_H
