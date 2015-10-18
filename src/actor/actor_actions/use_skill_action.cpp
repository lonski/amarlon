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

bool UseSkillAction::perform(ActorPtr user)
{
  _user = user;
  bool success = false;

  if ( _user && _skill )
  {
    success = _skill->use(_user, _target);
  }

  return success;
}

ActorActionUPtr UseSkillAction::clone()
{
  UseSkillActionUPtr cloned = std::make_unique<UseSkillAction>(_skill, _target);
  cloned->_user = _user;

  return std::move(cloned);
}

}

