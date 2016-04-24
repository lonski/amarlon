#ifndef SPECIES_TYPE_H
#define SPECIES_TYPE_H

#include <map>

namespace amarlon
{

enum class SpeciesType
{
  Null        = 0,
  Dragon      = 1,
  Enchanted   = 2,
  Lycanthrope = 3,
  Regenerator = 4,
  SpellUser   = 5,
  Undead      = 6,
  Humanoid    = 7
};

static std::map<SpeciesType, const char*> SpeciesType2Str {
  { SpeciesType::Null,        "None" },
  { SpeciesType::Dragon,      "Dragons" },
  { SpeciesType::Enchanted,   "Enchanted creatures" },
  { SpeciesType::Lycanthrope, "Lycanthropes" },
  { SpeciesType::Regenerator, "Regenerators" },
  { SpeciesType::SpellUser,   "Spell users" },
  { SpeciesType::Undead,      "Undead" },
  { SpeciesType::Humanoid,    "Humanoid" },
};

}

#endif // SPECIES_TYPE_H
