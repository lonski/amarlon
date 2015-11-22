#ifndef ANIMATION_DESCRIPTION
#define ANIMATION_DESCRIPTION

#include <memory>
#include <map>
#include <string>
#include <description.h>

namespace amarlon {

struct AnimationDescription;
typedef std::shared_ptr<AnimationDescription> AnimationDescriptionPtr;

struct AnimationDescription : Description
{
  AnimationDescription()
    : type(0)
  {
  }

  int type;
  std::map<std::string, std::string> params;
};

}

#endif // ANIMATION_DESCRIPTION

