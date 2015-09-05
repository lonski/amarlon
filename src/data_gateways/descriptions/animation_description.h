#ifndef ANIMATION_DESCRIPTION
#define ANIMATION_DESCRIPTION

#include <memory>
#include <animation_type.h>
#include <description.h>
#include <libtcod.hpp>

namespace amarlon {

struct AnimationDescription;
typedef std::shared_ptr<AnimationDescription> AnimationDescriptionPtr;

struct AnimationDescription : Description
{
  AnimationDescription()
    : type(animation::Type::Null)
    , color(TCODColor::white)
  {
  }

  animation::Type type;
  TCODColor color;
};

}

#endif // ANIMATION_DESCRIPTION

