#ifndef GLOW_H
#define GLOW_H

#include <animation.h>
#include <libtcod.hpp>

namespace amarlon { namespace animation {

class Blink;
typedef std::shared_ptr<Blink> BlinkPtr;

class Blink : public Animation
{
public:
  Blink(TCODColor targetColor = TCODColor::blue, int frameCount = 20, int frameDelay = 15);
  virtual AnimationPtr clone();
  virtual void run(TCODConsole& console);
  virtual Type getType() const;

  TCODColor getTargetColor() const;

private:
  TCODColor _targetColor;
  int _frames;
  int _frameDelay;

};

}}

#endif // GLOW_H
