#ifndef SPELLBOOK_DESCRIPTION
#define SPELLBOOK_DESCRIPTION

#include <vector>
#include <memory>
#include <description.h>

namespace amarlon
{

struct SpellSlotDescription : Description
{
  int level;
  int spell;
  bool prepared;
};

typedef std::shared_ptr<SpellSlotDescription> SpellSlotDescriptionPtr;

struct SpellbookDescription : Description
{
  std::vector<SpellSlotDescription> spellSlots;
  std::vector<int> knownSpells;
};

typedef std::shared_ptr<SpellbookDescription> SpellbookDescriptionPtr;

}

#endif // SPELLBOOK_DESCRIPTION

