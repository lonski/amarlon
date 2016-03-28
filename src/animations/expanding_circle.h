#ifndef EXPANDING_CIRCLE_H
#define EXPANDING_CIRCLE_H

#include <animation.h>
#include <libtcod.hpp>

namespace amarlon { namespace animation {

class ExpandingCircle;
typedef std::shared_ptr<ExpandingCircle> ExpandingCirclePtr;

class ExpandingCircle : public Animation
{
public:
  ExpandingCircle(TCODColor color = TCODColor::red, char ch = '*', int frameDelay = 15, int radius = 0);

  virtual AnimationPtr clone();
  virtual void run();
  virtual Type getType() const;

  virtual void load(const Params& params);
  virtual Params toParams() const;

private:
  TCODColor _color;
  char _ch;
  int _frameDelay;
  int _radius;

};

}}


#endif // EXPANDING_CIRCLE_H
