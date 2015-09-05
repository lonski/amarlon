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
  std::string name;
  int spellClass;
  int level;
  int targetType;
  int id;

  std::vector<EffectDescriptionPtr> effects;
  AnimationDescriptionPtr animation;
};

}

#endif // SPELL_DESCRIPTION

