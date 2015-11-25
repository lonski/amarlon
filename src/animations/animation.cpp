#include "animation.h"
#include <blink.h>
#include <throw.h>
#include <expanding_circle.h>
#include <blinking_circle.h>

namespace amarlon { namespace animation {

Animation::Animation()
{
}

Animation::~Animation()
{
}

AnimationPtr Animation::create(Type type)
{
  AnimationPtr a;

  switch(type)
  {
    case Type::Blink: a.reset( new Blink); break;
    case Type::Throw: a.reset( new Throw); break;
    case Type::ExpandingCircle: a.reset( new ExpandingCircle); break;
    case Type::BlinkingCircle: a.reset( new BlinkingCircle); break;
    default:;
  }
  return a;
}

void Animation::setLocation(const Target &startLoc, const Target &endLoc)
{
  _start = startLoc;
  _end = endLoc;
}

Target Animation::getStartLocation() const
{
  return _start;
}

Target Animation::getEndLocation() const
{
  return _end;
}

}}

