#include "throw.h"
#include <engine.h>
#include <chrono>
#include <thread>
#include <utils.h>
#include <console_utils.h>

namespace amarlon { namespace animation {

Throw::Throw(TCODColor color, char ch, int frameDelay)
  : _color(color)
  , _ch(ch)
  , _frameDelay(frameDelay)
{
}

AnimationPtr Throw::clone()
{
  return ThrowPtr( new Throw(*this) );
}

void Throw::run()
{
  TCODConsole& console = *TCODConsole::root;

  Target start  = getStartLocation();
  Target stop = getEndLocation();

  TCODPath* path = calculatePath(start, stop);
  while( path && !path->isEmpty() )
  {
    int x(0), y(0);
    path->walk(&x, &y, true);

    Engine::instance().render();
    setTile(x, y, _ch, _color);

    console.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(_frameDelay));
  }

  delete path;
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

