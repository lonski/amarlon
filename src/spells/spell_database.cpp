#include "spell_database.h"
#include <fstream>
#include <vector>
#include <spell.h>
#include <spell_factory.h>
#include <protobuf/spells.pb.h>

namespace amarlon {

SpellDatabase::SpellDatabase()
  : _factory( new SpellFactory )
  , _spellsData( new proto::SpellsData )
{
}

SpellDatabase::~SpellDatabase()
{
}

SpellPtr SpellDatabase::fetch(SpellId id)
{
  return _factory->produce( getSpellData(id) );
}

bool SpellDatabase::load(const std::string &fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    _spellsData->ParseFromIstream(&ifs);

    for( int i=0; i<_spellsData->spell_size(); ++i)
    {
      const proto::SpellData& sd = _spellsData->spell(i);
      printf("%s\n", sd.name().c_str());
    }

    return true;
  }
  return false;
}

proto::SpellData* SpellDatabase::getSpellData(SpellId id)
{
  for( int i=0; i<_spellsData->spell_size(); ++i)
  {
    const proto::SpellData& sd = _spellsData->spell(i);
    if ( sd.id() == static_cast<int>(id) ) return const_cast<proto::SpellData*>(&sd);
  }
  return nullptr;
}

std::string amarlon::SpellDatabase::getName(SpellId id)
{
  proto::SpellData* sd = getSpellData(id);
  return sd != nullptr ? sd->name() : "";
}

int SpellDatabase::getLevel(SpellId id)
{
  proto::SpellData* sd = getSpellData(id);
  return sd != nullptr ? sd->level() : 0;
}

CharacterClass SpellDatabase::getClass(SpellId id)
{
  proto::SpellData* sd = getSpellData(id);
  return sd != nullptr ? static_cast<CharacterClass>(sd->class_()) : CharacterClass::NoClass;
}

TargetType SpellDatabase::getTargetType(SpellId id)
{
  proto::SpellData* sd = getSpellData(id);
  return sd != nullptr ? static_cast<TargetType>(sd->target()) : TargetType::SELF;
}

int SpellDatabase::getRange(SpellId id)
{
  proto::SpellData* sd = getSpellData(id);
  return sd != nullptr ? sd->range() : 0;
}

int SpellDatabase::getRadius(SpellId id)
{
  proto::SpellData* sd = getSpellData(id);
  return sd != nullptr ? sd->radius() : 0;
}

std::string SpellDatabase::getScriptPath(SpellId id) const
{
  return "scripts/spells/" + std::to_string( static_cast<int>(id) ) + ".lua";
}

}

