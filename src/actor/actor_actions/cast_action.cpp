#include "cast_action.h"
#include <actor.h>
#include <spell.h>
#include <message_box.h>
#include <character_class.h>
#include <spell_book.h>

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
      if ( _spell->cast(_caster, _target) != CastResult::Nok )
      {
        //Set spell prepared = false in caster's spellbook
        CharacterPtr character = _caster->getFeature<Character>();
        if ( character && character->getSpellBook() )
        {
          auto sSlots = character->
                        getSpellBook()->
                        getSlots([&](SpellSlotPtr s){
                          return s->spell &&
                                 s->isPrepared &&
                                 s->spell->getId() == _spell->getId();
                        });

          if ( !sSlots.empty() )
          {
            sSlots.front()->isPrepared = false;
          }
        }

        result = ActorActionResult::Ok;
      }
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

