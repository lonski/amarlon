#include "scroll.h"
#include <spell.h>
#include <actor.h>
#include <character_class.h>
#include <spell_book.h>

namespace amarlon {

Scroll::Scroll()
{
}

Scroll::Scroll(const Scroll &rhs)
{
  *this = rhs;
}

Scroll::Scroll(const PickableData &data)
  : Pickable(data)
{
  _spell = Spell::create( static_cast<SpellId>(_data.spell_id()) );
}

Scroll::~Scroll()
{
}

bool Scroll::operator==(const Scroll &rhs) const
{
  return Pickable::operator ==(rhs);
}

Scroll &Scroll::operator=(const Scroll &rhs)
{
  Pickable::operator =(rhs);
  return *this;
}

bool Scroll::use(ActorPtr executor, const Target& target)
{
  if ( _spell )
  {
    CharacterPtr c = executor->getFeature<Character>();
    if ( c && c->getClass() && c->getClass()->getType() == _spell->getClass() )
    {
      _data.set_uses_count( getUsesCount() - 1);
      return _spell->cast(executor, target);
    }
  }
  return false;
}

bool Scroll::transcribe(ActorPtr transcriber)
{
  bool r = false;

  _data.set_uses_count( getUsesCount() - 1);

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
