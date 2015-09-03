#ifndef EFFECT_DESCRIPTION
#define EFFECT_DESCRIPTION

#include <memory>
#include <effect_type.h>
#include <description.h>

namespace amarlon {

struct EffectDescription;
typedef std::shared_ptr<EffectDescription> EffectDescriptionPtr;

struct EffectDescription : Description
{
  EffectDescription()
    : type(EffectType::Null)
    , lockId(0)
    , heal(0)
  {
  }

  EffectType type;
  int lockId;
  int heal;
};

}

#endif // EFFECT_DESCRIPTION

