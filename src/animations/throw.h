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
  Throw();
  virtual AnimationPtr clone();
  virtual void run(TCODConsole& console);
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
