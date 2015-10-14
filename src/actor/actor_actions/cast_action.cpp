#include "cast_action.h"
#include <actor.h>
#include <spell.h>
#include <message_box.h>

namespace amarlon {

CastAction::CastAction(SpellPtr spell, Target target)
  : _spell(spell)
  , _target(target)
{
}

CastAction::~CastAction()
{
}

bool CastAction::perform(ActorPtr caster)
{
  _caster = caster;
  bool success = false;

  if ( _caster && _spell )
  {
    CharacterPtr character = _caster->getFeature<Character>();
    if ( character )
    {
      _spell->cast(_caster, _target);
      success = true; //Casting action succedded, even if the spell failed
    }
  }

  return success;
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
  return _spell->getClass() == CharacterClass::NoClass || _spell->getClass() == character->getClass();
}

bool CastAction::isLevelCorrect() const
{
  CharacterPtr character = _caster->getFeature<Character>();
  return _spell->getLevel() <= character->getLevel();
}

}

