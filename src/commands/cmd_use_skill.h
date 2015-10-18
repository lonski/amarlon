#ifndef CMD_USE_SKILL_H
#define CMD_USE_SKILL_H

#include <memory>
#include <command.h>

namespace amarlon {

class Skill;
typedef std::shared_ptr<Skill> SkillPtr;

class CmdUseSkill : public Command
{
public:
  CmdUseSkill();

  virtual bool accept(TCOD_key_t &key);
  virtual int execute();

private:
  SkillPtr getSkill();

};

}
#endif // CMD_USE_SKILL_H
