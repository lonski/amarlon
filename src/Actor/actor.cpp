#include "actor.h"
#include "World/map.h"

Actor::Actor(const std::string &name, char ch, int x, int y, TCODColor color)
  : _x(x)
  , _y(y)
  , _ch(ch)
  , _name(name)
  , _color(color)
{
}

void Actor::move(int dx, int dy)
{
  _x += dx;
  _y += dy;
}

std::string Actor::getName() const
{
  return _name;
}

int Actor::getX() const
{
  return _x;
}

void Actor::setX(int x)
{
  _x = x;
}
int Actor::getY() const
{
  return _y;
}

void Actor::setY(int y)
{
  _y = y;
}
TCODColor Actor::getColor() const
{
  return _color;
}

char Actor::getChar() const
{
  return _ch;
}




