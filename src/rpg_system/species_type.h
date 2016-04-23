#ifndef SPECIES_TYPE_H
#define SPECIES_TYPE_H

#include <map>

namespace amarlon
{

enum class SpeciesType
{
  Null,
  Dragon,
  Enchanted,
  Lycanthrope,
  Regenerator,
  SpellUser,
  Undead
};

static std::map<SpeciesType, const char*> SpeciesType2Str {
  { SpeciesType::Null,        "None" },
  { SpeciesType::Dragon,      "Dragons" },
  { SpeciesType::Enchanted,   "Enchanted creatures" },
  { SpeciesType::Lycanthrope, "Lycanthropes" },
  { SpeciesType::Regenerator, "Regenerators" },
  { SpeciesType::SpellUser,   "Spell users" },
  { SpeciesType::Undead,      "Undead" },
};

}

#endif // SPECIES_TYPE_H
