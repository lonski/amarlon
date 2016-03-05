#include "spell_db.h"
#include <fstream>
#include <vector>
#include <spell.h>
#include <xml/rapidxml_print.hpp>
#include <xml/rapidxml.hpp>

namespace amarlon {

SpellDB::SpellDB()
{

}

SpellDB::~SpellDB()
{

}

bool SpellDB::load(const std::string &fn)
{
  std::ifstream ifs(fn);
  if ( ifs.is_open() )
  {
    _spells.ParseFromIstream(&ifs);
    return true;
  }
  return false;
}

std::vector<SpellPtr> SpellDB::getSpells(std::function<bool (SpellPtr)> filter)
{
  std::vector<SpellPtr> spells;

  for ( auto it = _spells.spell().begin(); it != _spells.spell().end(); ++it )
  {
    SpellPtr s = fetch( static_cast<SpellId>(it->id()) );
    if ( filter(s) ) spells.push_back(s);
  }

  return spells;
}

SpellPtr SpellDB::fetch(SpellId id)
{
  if ( id != SpellId::Null )
  {
    for ( auto it = _spells.spell().begin(); it != _spells.spell().end(); ++it )
    {
      if ( static_cast<SpellId>(it->id()) == id)
      {
        return SpellPtr( new Spell(&(*it)) );
      }
    }
  }

  return nullptr;
}

}

