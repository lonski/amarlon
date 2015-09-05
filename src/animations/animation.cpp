#include "animation.h"
#include <blink.h>
#include <throw.h>

namespace amarlon { namespace animation {

Animation::Animation()
{
}

Animation::~Animation()
{
}

AnimationPtr Animation::create(AnimationDescriptionPtr dsc)
{
  AnimationPtr a;
  if ( dsc )
  {
    switch(dsc->type)
    {
      case Type::Blink: a.reset( new Blink ); break;
      case Type::Throw: a.reset( new Throw ); break;
      default:;
    }    
  }

  if ( a ) a->load( dsc->params );

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
