#include "spell_book.h"
#include <algorithm>
#include <spell.h>
#include <actor_descriptions.h>
#include <engine.h>
#include <spell_db.h>

namespace amarlon {

SpellBook::SpellBook()
{

}

SpellBookPtr SpellBook::create(SpellbookDescription dsc)
{
  SpellBookPtr sb( new SpellBook );
  for ( auto s : dsc.spellSlots )
  {
    sb->addSlot( new SpellSlot( s.level, s.prepared, Spell::create((SpellId)s.spell) ) );
  }

  for ( auto s : dsc.knownSpells )
  {
    sb->addKnownSpell( Spell::create((SpellId)s) );
  }

  return sb;
}

SpellbookDescriptionPtr SpellBook::toDescriptionStruct()
{
  SpellbookDescriptionPtr dsc(new SpellbookDescription);
  for ( SpellPtr ks : _knownSpells )
  {
    dsc->knownSpells.push_back( (int)ks->getId() );
  }
  for ( SpellSlotPtr ss : _spellSlots  )
  {
    dsc->spellSlots.push_back( *ss->toDescriptionStruct() );
  }
  return dsc;
}

std::vector<SpellSlotPtr> SpellBook::getSlots(std::function<bool(SpellSlotPtr)> filter) const
{
  std::vector<SpellSlotPtr> spells;
  for(auto s : _spellSlots) if ( filter(s) ) spells.push_back(s);

  return spells;
}

std::vector<SpellPtr> SpellBook::getKnownSpells(std::function<bool(SpellPtr)> filter) const
{
  std::vector<SpellPtr> spells;
  for(auto s : _knownSpells) if ( filter(s) ) spells.push_back(s);
  return spells;
}

void SpellBook::addSlot(SpellSlotPtr slot)
{
  _spellSlots.push_back(slot);
}

void SpellBook::addSlot(SpellSlot *slot)
{
  addSlot( SpellSlotPtr(slot) );
}

void SpellBook::addKnownSpell(SpellPtr spell)
{
  auto it = std::find(_knownSpells.begin(), _knownSpells.end(), spell);
  if ( it == _knownSpells.end() ) _knownSpells.push_back(spell);
}

void SpellBook::addKnownSpell(Spell *spell)
{
  addKnownSpell( SpellPtr(spell) );
}

void SpellBook::addKnownSpells(CharacterClassType c, int level)
{
  auto spells = Engine::instance().getSpellDB().getSpells([&](SpellPtr s){
    return s->getClass() == c && s->getLevel() == level;
  });

  for ( auto s : spells ) addKnownSpell( s );
}

bool SpellBook::knowSpell(SpellPtr spell)
{
  return !getKnownSpells([&](SpellPtr s){ return s == spell; }).empty();
}

int SpellBook::getSlotCount(int level) const
{
  return getSlots([&level](SpellSlotPtr s){ return s->level == level; }).size();
}

void SpellBook::prepareSpells()
{
  for(auto s : _spellSlots) s->isPrepared = true;
}

bool SpellBook::operator==(const SpellBook &rhs)
{
  bool e = true;
  e &= _knownSpells.size() == rhs._knownSpells.size();
  e &= std::equal(_knownSpells.begin(), _knownSpells.end(), rhs._knownSpells.begin());
  e &= std::equal(_spellSlots.begin(), _spellSlots.end(), rhs._spellSlots.begin());
  return e;
}

SpellBookPtr SpellBook::clone()
{
  SpellBookPtr sb(new SpellBook);
  for ( auto s : _spellSlots ) sb->addSlot( new SpellSlot(*s) );
  for ( auto s : _knownSpells ) sb->addKnownSpell( Spell::create(s->getId()) );

  return sb;
}

}

