#ifndef SPELL_GATEWAY_H
#define SPELL_GATEWAY_H

#include <map>
#include <memory>
#include <vector>
#include <spell_id.h>
#include <character_class_type.h>
#include <target_type.h>
#include <spell.pb.h>

namespace amarlon {

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class SpellDB
{
public:
  SpellDB();
  virtual ~SpellDB();

  virtual std::vector<SpellPtr> getSpells(std::function<bool (SpellPtr)> filter );
  virtual SpellPtr fetch(SpellId id);
  virtual bool load(const std::string& fn);

protected:
  SpellsData _spells;

};

}

#endif // SPELL_GATEWAY_H
