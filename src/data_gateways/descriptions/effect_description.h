#ifndef EFFECT_DESCRIPTION
#define EFFECT_DESCRIPTION

#include <memory>
#include <map>
#include <string>
#include <effect_type.h>
#include <description.h>

namespace amarlon {

struct EffectDescription;
typedef std::shared_ptr<EffectDescription> EffectDescriptionPtr;

struct EffectDescription : Description
{
  EffectDescription()
    : type(EffectType::Null)
  {
  }

  EffectType type;
  std::map<std::string, std::string> params;
};

}

#endif // EFFECT_DESCRIPTION

