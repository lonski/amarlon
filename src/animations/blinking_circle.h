#ifndef BLINKING_CIRCLE_H
#define BLINKING_CIRCLE_H

#include <animation.h>
#include <libtcod.hpp>

namespace amarlon { namespace animation {

class BlinkingCircle;
typedef std::shared_ptr<BlinkingCircle> BlinkingCirclePtr;

class BlinkingCircle : public Animation
{
public:
  BlinkingCircle(TCODColor targetColor = TCODColor::blue, int radius = 0, int frameCount = 20, int frameDelay = 15);
  virtual AnimationPtr clone();
  virtual void run();
  virtual Type getType() const;

  TCODColor getTargetColor() const;

  virtual void load(const Params& params);
  virtual Params toParams() const;

private:
  TCODColor _targetColor;
  int _frames;
  int _frameDelay;
  int _radius;

};

}}

#endif // BLINKING_CIRCLE_H
