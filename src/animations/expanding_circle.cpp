#include "expanding_circle.h"
#include <engine.h>
#include <chrono>
#include <thread>
#include <utils.h>
#include <console_utils.h>


namespace amarlon { namespace animation {

ExpandingCircle::ExpandingCircle(TCODColor color, char ch, int frameDelay, int radius)
  : _color(color)
  , _ch(ch)
  , _frameDelay(frameDelay)
  , _radius(radius)
{
}

AnimationPtr ExpandingCircle::clone()
{
  return ExpandingCirclePtr( new ExpandingCircle(*this) );
}

void ExpandingCircle::run()
{
  TCODConsole& console = *TCODConsole::root;

  //Target start  = getStartLocation();
  Target stop = getEndLocation();
  for(int r = 0; r <= _radius; ++r)
  {
    Engine::instance().render();
    drawCircle(r, stop, _ch, _color);
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
  auto it = params.find("circle_color");
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
    {"circle_color",  colorToStr(_color) },
    {"delay",  toStr<int>(_frameDelay)  },
    {"char",   std::string(_ch, 1) },
    {"radius", toStr<int>(_radius) }
  };
}

}}

