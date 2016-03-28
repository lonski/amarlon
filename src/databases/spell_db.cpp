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
    _spells.clear();

    SpellsData spells;
    spells.ParseFromIstream(&ifs);

    for ( auto it = spells.spell().begin(); it != spells.spell().end(); ++it )
    {
      _spells[ static_cast<SpellId>(it->id()) ] = SpellPtr(new Spell(*it));
    }

    return true;
  }
  return false;
}

std::vector<SpellPtr> SpellDB::getSpells(std::function<bool (SpellPtr)> filter)
{
  std::vector<SpellPtr> spells;

  for ( const auto& kv : _spells )
  {
    if ( filter(kv.second) ) spells.push_back( kv.second->clone() );
  }

  return spells;
}

SpellPtr SpellDB::fetch(SpellId id)
{
  if ( id != SpellId::Null )
  {
    auto it = _spells.find(id);
    if ( it != _spells.end() ) return it->second->clone();
  }

  return nullptr;
}

}

