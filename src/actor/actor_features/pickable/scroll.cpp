#include "scroll.h"
#include <spell.h>
#include <pickable_description.h>
#include <actor.h>
#include <character_class.h>
#include <spell_book.h>

namespace amarlon {

Scroll::Scroll(DescriptionPtr dsc)
  : Pickable(dsc)
{
  ScrollDescriptionPtr pDsc = std::dynamic_pointer_cast<ScrollDescription>(dsc);
  if ( pDsc != nullptr )
  {
    _spell = Spell::create( static_cast<SpellId>(pDsc->spellId) );
  }
}

DescriptionPtr Scroll::toDescriptionStruct(ActorFeaturePtr cmp)
{
  ScrollDescriptionPtr dsc(new ScrollDescription);
  ScrollPtr cmpP = std::dynamic_pointer_cast<Scroll>(cmp);

  Pickable::toDescriptionStruct(dsc, cmpP);

  if ( cmpP )
  {
    if ( _spell )
    {
      if ( cmpP->_spell->getId() != _spell->getId() ) dsc->spellId = (int)_spell->getId();
    }
  }
  else
  {
    if ( _spell )
    {
      dsc->spellId = (int)_spell->getId();
    }
  }

  return dsc;
}

Scroll::~Scroll()
{
}

ActorFeaturePtr Scroll::clone()
{
  ScrollPtr cloned( new Scroll );

  Pickable::clone( cloned.get() );
  cloned->_spell = _spell;

  return cloned;
}

bool Scroll::isEqual(ActorFeaturePtr rhs) const
{
  ScrollPtr scroll = std::dynamic_pointer_cast<Scroll>(rhs);
  if ( scroll )
  {
    return Pickable::isEqual(rhs) && _spell == scroll->_spell;
  }
  return false;
}

bool Scroll::use(ActorPtr executor, const Target& target)
{
  if ( _spell )
  {
    CharacterPtr c = executor->getFeature<Character>();
    if ( c && c->getClass() && c->getClass()->getType() == _spell->getClass() )
    {
      --_usesCount;
      return _spell->cast(executor, target);
    }
  }
  return false;
}

bool Scroll::transcribe(ActorPtr transcriber)
{
  bool r = false;

  --_usesCount;
  if ( _spell )
  {
    if ( CharacterPtr c = transcriber->getFeature<Character>() )
    {
      if ( SpellBookPtr sb = c->getSpellBook() )
      {
        int levelDiff = c->getLevel() - _spell->getLevel();
        if ( c->abilityRoll( AbilityScore::INT, levelDiff ) )
        {
          sb->addKnownSpell( _spell );
          r = true;
        }
      }
    }
  }

  return r;
}

SpellPtr Scroll::getSpell() const
{
  return _spell;
}

bool Scroll::isUsable() const
{
  return _spell != nullptr;
}

TargetType Scroll::getTargetType() const
{
  return _spell ? _spell->getTargetType() : TargetType::SELF;
}

int Scroll::getRange() const
{
  return _spell ? _spell->getRange() : Pickable::getRange();
}

int Scroll::getRadius() const
{
  return _spell ? _spell->getRadius() :  Pickable::getRadius();;
}

}
