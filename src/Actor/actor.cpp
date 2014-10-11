#include "actor.h"
#include "World/map.h"
#include <iostream>

ActorDB Actor::DB;

Actor::Actor(ActorType aId, int x, int y)
  : afContainer(nullptr)
  , afPickable(nullptr)
  , afDestrucible(nullptr)
  , _id(aId)
  , _x(x)
  , _y(y)
{
  afContainer = Actor::DB.getContainer(aId);
  afPickable = Actor::DB.getPickable(aId);
  afDestrucible = Actor::DB.getDestrucible(aId);
}

void Actor::move(int dx, int dy)
{
  _x += dx;
  _y += dy;
}

void Actor::morph(ActorType newType)
{
  _id = newType;
}

bool Actor::isAlive() const
{
  return  afDestrucible && afDestrucible->isAlive();
}

bool Actor::isFovOnly() const
{
  return Actor::DB.isFovOnly(_id);
}

bool Actor::isTransparent() const
{
  return Actor::DB.isTransparent(_id);
}

bool Actor::blocks() const
{
  return Actor::DB.blocks(_id);;
}

ActorType Actor::getId() const
{
  return _id;
}

std::string Actor::getName() const
{
  return Actor::DB.getName(_id);;
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
  return Actor::DB.getColor(_id);;
}

unsigned char Actor::getChar() const
{
  return Actor::DB.getChar(_id);;
}




