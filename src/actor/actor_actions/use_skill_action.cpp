#include "use_skill_action.h"
#include <skill.h>

namespace amarlon {

UseSkillAction::UseSkillAction(SkillPtr skill, Target target)
  : _skill(skill)
  , _target(target)
{
}

UseSkillAction::~UseSkillAction()
{
}

ActorActionResult UseSkillAction::perform(ActorPtr user)
{
  _user = user;
  ActorActionResult r = ActorActionResult::Nok;

  if ( _user && _skill )
  {
    r = _skill->use(_user, _target) ? ActorActionResult::Ok
                                    : ActorActionResult::Nok;
  }

  return r;
}

ActorActionUPtr UseSkillAction::clone()
{
  UseSkillActionUPtr cloned = std::make_unique<UseSkillAction>(_skill, _target);
  cloned->_user = _user;

  return std::move(cloned);
}

}

