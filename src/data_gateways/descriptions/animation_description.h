#ifndef ANIMATION_DESCRIPTION
#define ANIMATION_DESCRIPTION

#include <memory>
#include <animation_type.h>
#include <description.h>
#include <libtcod.hpp>
#include <map>
#include <string>

namespace amarlon {

struct AnimationDescription;
typedef std::shared_ptr<AnimationDescription> AnimationDescriptionPtr;

struct AnimationDescription : Description
{
  AnimationDescription()
    : type(animation::Type::Null)
  {
  }

  animation::Type type;
  std::map<std::string, std::string> params;
};

}

#endif // ANIMATION_DESCRIPTION

