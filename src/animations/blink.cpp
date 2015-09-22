#include "blink.h"
#include <engine.h>
#include <chrono>
#include <thread>
#include <utils.h>

namespace amarlon { namespace animation {

Blink::Blink(TCODColor targetColor, int frameCount, int frameDelay)
  : _targetColor(targetColor)
  , _frames(frameCount)
  , _frameDelay(frameDelay)
{
}

AnimationPtr Blink::clone()
{
  return BlinkPtr( new Blink(*this) );
}

void Blink::run(TCODConsole& console)
{
  Target target = getEndLocation();

  TCODColor originalColor = console.getCharForeground(target.x, target.y);
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

    console.setCharForeground(target.x, target.y, newColor);
    console.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(_frameDelay));
  }

  for(int f = 0; f < _frames/2; ++f)
  {
    newColor.r -= rStep;
    newColor.g -= gStep;
    newColor.b -= bStep;

    console.setCharForeground(target.x, target.y, newColor);
    console.flush();
    std::this_thread::sleep_for(std::chrono::milliseconds(_frameDelay));
  }

}

Type Blink::getType() const
{
  return Type::Blink;
}

TCODColor Blink::getTargetColor() const
{
  return _targetColor;
}

void Blink::load(const Params &params)
{
  auto it = params.find("color");
  _targetColor = it != params.end() ? strToColor( it->second ) : TCODColor::blue;

  it = params.find("frames");
  _frames = it != params.end() ? fromStr<int>( it->second ) : 20;

  it = params.find("delay");
  _frameDelay = it != params.end() ? fromStr<int>( it->second ) : 15;
}

Params Blink::toParams() const
{
  return {
    {"color",  colorToStr(_targetColor) },
    {"frames", toStr<int>(_frames)      },
    {"delay",  toStr<int>(_frameDelay)  }
  };
}

}}

