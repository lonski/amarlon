#ifndef SPELLFACTORY
#define SPELLFACTORY

#include <memory>
#include <spell_id.h>

namespace amarlon {

namespace proto {
  class SpellData;
}

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class SpellFactory {
public:
  SpellPtr produce(proto::SpellData* spellData);

};

}

#endif // SPELLFACTORY

