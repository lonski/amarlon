#ifndef SPELL_GATEWAY_H
#define SPELL_GATEWAY_H

#include <map>
#include <memory>
#include <spell_id.h>
#include <character_classes.h>
#include <target_type.h>

namespace amarlon {

class Spell;
class SpellFactory;
typedef std::shared_ptr<Spell> SpellPtr;
typedef std::shared_ptr<SpellFactory> SpellFactoryPtr;

namespace proto {
  class SpellData;
  class SpellsData;
  typedef std::shared_ptr<SpellsData> SpellsDataPtr;
}

class SpellDatabase
{
public:
  SpellDatabase();
  ~SpellDatabase();

  SpellPtr fetch(SpellId id);
  std::string getName(SpellId id);
  int getLevel(SpellId id);
  CharacterClass getClass(SpellId id);
  TargetType getTargetType(SpellId id);
  int getRange(SpellId id);
  int getRadius(SpellId id);
  std::string getScriptPath(SpellId id) const;

  bool load(const std::string& fn);

protected:
  SpellFactoryPtr _factory;
  proto::SpellsDataPtr _spellsData;

  proto::SpellData* getSpellData(SpellId id);

};

}

#endif // SPELL_GATEWAY_H
