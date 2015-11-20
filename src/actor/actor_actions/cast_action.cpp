#include "cast_action.h"
#include <actor.h>
#include <spell.h>
#include <message_box.h>
#include <character_class.h>

namespace amarlon {

CastAction::CastAction(SpellPtr spell, Target target)
  : _spell(spell)
  , _target(target)
{
}

CastAction::~CastAction()
{
}

ActorActionResult CastAction::perform(ActorPtr caster)
{
  _caster = caster;
  ActorActionResult result = ActorActionResult::Nok;

  if ( _caster && _spell )
  {
    CharacterPtr character = _caster->getFeature<Character>();
    if ( character )
    {
      _spell->cast(_caster, _target);
      result = ActorActionResult::Ok; //Casting action succedded, even if the spell failed
    }
  }

  return result;
}

ActorActionUPtr CastAction::clone()
{
  CastActionUPtr cloned = std::make_unique<CastAction>(_spell, _target);
  cloned->_caster = _caster;

  return std::move(cloned);
}

bool CastAction::isClassCorrect() const
{
  CharacterPtr character = _caster->getFeature<Character>();
  return _spell->getClass() == CharacterClassType::NoClass || _spell->getClass() == character->getClass()->getType();
}

bool CastAction::isLevelCorrect() const
{
  CharacterPtr character = _caster->getFeature<Character>();
  return _spell->getLevel() <= character->getLevel();
}

}

