#include "throw.h"
#include <engine.h>
#include <chrono>
#include <thread>
#include <utils.h>

namespace amarlon { namespace animation {

Throw::Throw()
  : _color(TCODColor::red)
  , _ch('*')
  , _frameDelay(15)
{
}

AnimationPtr Throw::clone()
{
  return ThrowPtr( new Throw(*this) );
}

void Throw::run(TCODConsole& console)
{
  Target loc  = getStartLocation();
  Target stop = getEndLocation();

  while( loc.x != stop.x || loc.y != stop.y)
  {
    if (loc.x != stop.x ) loc.x < stop.x ? ++loc.x : --loc.x;
    if (loc.y != stop.y ) loc.y < stop.y ? ++loc.y : --loc.y;

    Engine::instance().render();
    console.putChar(loc.x, loc.y, _ch);
    console.setCharForeground(loc.x, loc.y, _color);
    console.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(_frameDelay));
  }

}

Type Throw::getType() const
{
  return Type::Throw;
}


void Throw::load(const Params &params)
{
  auto it = params.find("color");
  _color = it != params.end() ? strToColor( it->second ) : TCODColor::blue;

  it = params.find("delay");
  _frameDelay = it != params.end() ? fromStr<int>( it->second ) : 15;

  it = params.find("char");
  _ch = it != params.end() ? it->second.front() : 15;
}

Params Throw::toParams() const
{
  return {
    {"color",  colorToStr(_color) },
    {"delay",  toStr<int>(_frameDelay)  },
    {"char",   std::string(_ch, 1)  }
  };
}

}}
