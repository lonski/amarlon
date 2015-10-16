#include "blinking_circle.h"
#include <engine.h>
#include <chrono>
#include <thread>
#include <utils.h>
#include <console_utils.h>

namespace amarlon { namespace animation {

BlinkingCircle::BlinkingCircle(TCODColor targetColor, int radius, int frameCount, int frameDelay)
  : _targetColor(targetColor)
  , _frames(frameCount)
  , _frameDelay(frameDelay)
  , _radius(radius)
{
}

AnimationPtr BlinkingCircle::clone()
{
  return BlinkingCirclePtr( new BlinkingCircle(*this) );
}

void BlinkingCircle::run()
{
  TCODConsole& console = *TCODConsole::root;
  Engine::instance().render();
  console.flush();

  Target target = getEndLocation();

  TCODColor originalColor = TCODColor::black;
  TCODColor newColor = originalColor;

  int rDiff = _targetColor.r - originalColor.r;
  int rStep = rDiff / (_frames / 2);
  int gDiff = _targetColor.g - originalColor.g;
  int gStep = gDiff / (_frames / 2);
  int bDiff = _targetColor.b - originalColor.b;
  int bStep = bDiff / (_frames / 2);

  for(int f = 0; f < _frames/2; ++f)
  {
    newColor.r += rStep;
    newColor.g += gStep;
    newColor.b += bStep;

    highlightFilledCircle(_radius, target, newColor);

    console.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(_frameDelay));
  }

  for(int f = 0; f < _frames/2; ++f)
  {
    newColor.r -= rStep;
    newColor.g -= gStep;
    newColor.b -= bStep;

    highlightFilledCircle(_radius, target, newColor);

    console.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(_frameDelay));
  }

  Engine::instance().render();
  console.flush();
}

Type BlinkingCircle::getType() const
{
  return Type::BlinkingCircle;
}

TCODColor BlinkingCircle::getTargetColor() const
{
  return _targetColor;
}

void BlinkingCircle::load(const Params &params)
{
  auto it = params.find("color");
  _targetColor = it != params.end() ? strToColor( it->second ) : TCODColor::blue;

  it = params.find("frames");
  _frames = it != params.end() ? fromStr<int>( it->second ) : 20;

  it = params.find("delay");
  _frameDelay = it != params.end() ? fromStr<int>( it->second ) : 15;

  it = params.find("radius");
  _radius = it != params.end() ? fromStr<int>( it->second ) : 0;
}

Params BlinkingCircle::toParams() const
{
  return {
    {"color",  colorToStr(_targetColor) },
    {"frames", toStr<int>(_frames)      },
    {"delay",  toStr<int>(_frameDelay)  },
    {"radius", toStr<int>(_radius) }
  };
}

}}
