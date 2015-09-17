#include "expanding_circle.h"
#include <engine.h>
#include <chrono>
#include <thread>
#include <utils.h>
#include <console_utils.h>


namespace amarlon { namespace animation {

ExpandingCircle::ExpandingCircle()
  : _color(TCODColor::red)
  , _ch('*')
  , _frameDelay(15)
  , _radius(0)
{
}

AnimationPtr ExpandingCircle::clone()
{
  return ExpandingCirclePtr( new ExpandingCircle(*this) );
}

void ExpandingCircle::run(TCODConsole& console)
{
  //Target start  = getStartLocation();
  Target stop = getEndLocation();
  for(int r = 0; r <= _radius; ++r)
  {
    Engine::instance().render();
    drawCircle(r, stop);
    console.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(_frameDelay));
  }
}

Type ExpandingCircle::getType() const
{
  return Type::ExpandingCircle;
}

void ExpandingCircle::load(const Params &params)
{
  auto it = params.find("color");
  _color = it != params.end() ? strToColor( it->second ) : TCODColor::blue;

  it = params.find("delay");
  _frameDelay = it != params.end() ? fromStr<int>( it->second ) : 15;

  it = params.find("char");
  _ch = it != params.end() ? it->second.front() : 15;

  it = params.find("radius");
  _radius = it != params.end() ? fromStr<int>( it->second ) : 0;
}

Params ExpandingCircle::toParams() const
{
  return {
    {"color",  colorToStr(_color) },
    {"delay",  toStr<int>(_frameDelay)  },
    {"char",   std::string(_ch, 1) },
    {"radius", toStr<int>(_radius) }
  };
}

}}
