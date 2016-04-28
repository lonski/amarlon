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
}

Scroll::~Scroll()
{
}

ActorFeaturePtr Scroll::clone()
{
  ScrollPtr cloned( new Scroll );

  Pickable::clone( cloned.get() );

  return cloned;
}

bool Scroll::isEqual(ActorFeaturePtr rhs) const
{
  ScrollPtr scroll = std::dynamic_pointer_cast<Scroll>(rhs);
  if ( scroll )
  {
    return Pickable::isEqual(rhs);
  }
  return false;
}

bool Scroll::use(ActorPtr executor, const Target& target)
{
  if ( getSpell() )
  {
    --_usesCount;
    return getSpell()->cast(executor, target) != CastResult::Nok;
  }
  return false;
}

bool Scroll::transcribe(ActorPtr transcriber)
{
  bool r = false;

  --_usesCount;
  if ( getSpell() )
  {
    if ( CharacterPtr c = transcriber->getFeature<Character>() )
    {
      if ( SpellBookPtr sb = c->getSpellBook() )
      {
        int levelDiff = c->getLevel() - getSpell()->getLevel();
        if ( c->abilityRoll( AbilityScore::INT, levelDiff ) )
        {
          sb->addKnownSpell( getSpell() );
          r = true;
        }
      }
    }
  }

  return r;
}

bool Scroll::isUsable() const
{
  return getSpell() != nullptr;
}

TargetType Scroll::getTargetType() const
{
  return getSpell() ? getSpell()->getTargetType() : TargetType::SELF;
}

int Scroll::getRange() const
{
  return getSpell() ? getSpell()->getRange() : Pickable::getRange();
}

int Scroll::getRadius() const
{
  return getSpell() ? getSpell()->getRadius() :  Pickable::getRadius();;
}

}
