#ifndef USE_SKILL_ACTION_H
#define USE_SKILL_ACTION_H

#include <memory>
#include <actor_action.h>
#include <target.h>

namespace amarlon {

class Skill;
typedef std::shared_ptr<Skill> SkillPtr;

class UseSkillAction : public ActorAction
{
public:
    UseSkillAction(SkillPtr skill, Target target);
    virtual ~UseSkillAction();

    virtual ActorActionResult perform(ActorPtr user);
    virtual ActorActionUPtr clone();

private:
    SkillPtr _skill;
    ActorPtr _user;
    Target _target;
};

typedef std::shared_ptr<UseSkillAction> UseSkillActionPtr;
typedef std::unique_ptr<UseSkillAction> UseSkillActionUPtr;

}

#endif // USE_SKILL_ACTION_H
