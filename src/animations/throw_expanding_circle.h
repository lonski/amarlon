#ifndef THROW_EXPANDING_CIRCLE_H
#define THROW_EXPANDING_CIRCLE_H

#include <animation.h>
#include <libtcod.hpp>
#include <throw.h>
#include <expanding_circle.h>

namespace amarlon { namespace animation {

class ThrowExpandingCircle;
typedef std::shared_ptr<ThrowExpandingCircle> ThrowExpandingCirclePtr;

class ThrowExpandingCircle : public Animation
{
public:
  ThrowExpandingCircle();
  virtual AnimationPtr clone();
  virtual void run(TCODConsole& console);
  virtual Type getType() const;

  virtual void load(const Params& params);
  virtual Params toParams() const;

private:
  Throw _throw;
  ExpandingCircle _circle;

};

}}

#endif // THROW_EXPANDING_CIRCLE_H
