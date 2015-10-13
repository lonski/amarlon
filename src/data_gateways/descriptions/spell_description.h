#ifndef SPELL_DESCRIPTION
#define SPELL_DESCRIPTION

#include <memory>
#include <set>
#include <vector>
#include <description.h>

namespace amarlon {

struct SpellDescription;
typedef std::shared_ptr<SpellDescription> SpellDescriptionPtr;

struct SpellDescription : Description
{
  SpellDescription()
    : spellClass(0)
    , level(0)
    , targetType(0)
    , range(0)
    , id(0)
    , radius(0)
  {}

  std::string name;
  int spellClass;
  int level;
  int targetType;
  int range;
  int id;
  int radius;
  std::string description;
};

}

#endif // SPELL_DESCRIPTION

