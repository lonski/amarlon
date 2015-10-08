#include "spell_factory.h"
#include <spell.h>
#include <spells.pb.h>

namespace amarlon {

SpellPtr SpellFactory::produce(proto::SpellData *spellData)
{
  SpellPtr spell;
  if ( spellData != nullptr )
  {
    spell.reset(new Spell(static_cast<SpellId>(spellData->id()), spellData));
  }
  return spell;
}

}
