#ifndef SPELL_DESCRIPTION
#define SPELL_DESCRIPTION

#include <memory>
#include <vector>
#include <description.h>
#include <effect_description.h>
#include <animation_description.h>

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
  {}

  std::string name;
  int spellClass;
  int level;
  int targetType;
  int range;
  int id;

  std::vector<EffectDescriptionPtr> effects;
  AnimationDescriptionPtr animation;
};

}

#endif // SPELL_DESCRIPTION

