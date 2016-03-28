#ifndef THROW_H
#define THROW_H

#include <animation.h>
#include <libtcod.hpp>

namespace amarlon { namespace animation {

class Throw;
typedef std::shared_ptr<Throw> ThrowPtr;

class Throw : public Animation
{
public:
  Throw(TCODColor color = TCODColor::red, char ch = '*', int frameDelay = 15 );
  virtual AnimationPtr clone();
  virtual void run();
  virtual Type getType() const;

  virtual void load(const Params& params);
  virtual Params toParams() const;

private:
  TCODColor _color;
  char _ch;
  int _frameDelay;

};

}}

#endif // THROW_H
