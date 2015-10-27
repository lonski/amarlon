#include "scroll.h"
#include <spell.h>
#include <pickable_description.h>

namespace amarlon {

Scroll::Scroll(bool stackable, int amount)
  : Pickable(stackable, amount)
{
}

Scroll::Scroll(DescriptionPtr dsc)
  : Pickable(dsc)
{
  ScrollDescriptionPtr pDsc = std::dynamic_pointer_cast<ScrollDescription>(dsc);
  if ( pDsc != nullptr )
  {
    _spell = Spell::create( static_cast<SpellId>(pDsc->spellId) );
  }
}

Scroll::~Scroll()
{
}

ActorFeaturePtr Scroll::clone()
{
  ScrollPtr cloned( new Scroll );

  Pickable::clone( cloned.get() );
  cloned->_spell = _spell->clone();

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
  return _spell->cast(executor, target);
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
