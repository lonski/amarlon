#include "throw_expanding_circle.h"

namespace amarlon { namespace animation {

ThrowExpandingCircle::ThrowExpandingCircle()
{
}

AnimationPtr ThrowExpandingCircle::clone()
{
  return ThrowExpandingCirclePtr( new ThrowExpandingCircle(*this) );
}

void ThrowExpandingCircle::run(TCODConsole &console)
{
  _throw.setLocation( getStartLocation(), getEndLocation() );\
  _circle.setLocation( getStartLocation(), getEndLocation() );

  _throw.run(console);
  _circle.run(console);
}

Type ThrowExpandingCircle::getType() const
{
  return Type::ThrowExpandingCircle;
}

void ThrowExpandingCircle::load(const Params &params)
{
  _throw.load(params);
  _circle.load(params);
}

Params ThrowExpandingCircle::toParams() const
{
  Params p1 = _throw.toParams();
  Params p2 = _circle.toParams();

  p2.insert(p1.begin(), p1.end());
  return p2;
}

}}
