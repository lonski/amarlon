#ifndef ANIMATION_H
#define ANIMATION_H

#include <target.h>
#include <memory>
#include <libtcod.hpp>
#include <animation_description.h>
#include <animation_type.h>

namespace amarlon { namespace animation {

class Animation;
typedef std::shared_ptr<Animation> AnimationPtr;

class Animation
{
public:
  Animation();
  virtual ~Animation();

  static AnimationPtr create(AnimationDescriptionPtr dsc);
  virtual AnimationPtr clone() = 0;
  virtual void run(TCODConsole& console) = 0;
  virtual Type getType() const = 0;

  virtual void setLocation(const Target& startLoc, const Target& endLoc);
  virtual Target getStartLocation() const;
  virtual Target getEndLocation() const;

private:
  Target _start;
  Target _end;

};

}}

#endif // ANIMATION_H
