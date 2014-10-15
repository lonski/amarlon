#include "Actor.h"
#include "World/Map.h"
#include <iostream>

ActorDB Actor::DB;
Actor* Actor::Player(nullptr);

Actor::Actor(ActorType aId, int x, int y)
  : _id(aId)
  , _x(x)
  , _y(y)
{  
  setAfContainer  ( Actor::DB.getContainer  (aId) );
  setAfPickable   ( Actor::DB.getPickable   (aId) );
  setAfDestrucible( Actor::DB.getDestrucible(aId) );
  setAfAttacker   ( Actor::DB.getAttacker   (aId) );
  setAfAi         ( Actor::DB.getAi         (aId) );
}

void Actor::move(int dx, int dy)
{
  _x += dx;
  _y += dy;
}

void Actor::morph(ActorType newType)
{
  _id = newType;

  delete _afContainer;
  delete _afPickable;
  delete _afDestrucible;
  delete _afAttacker;
  delete _afAi;

  setAfContainer  ( Actor::DB.getContainer  (_id) );
  setAfPickable   ( Actor::DB.getPickable   (_id) );
  setAfDestrucible( Actor::DB.getDestrucible(_id) );
  setAfAttacker   ( Actor::DB.getAttacker   (_id) );
  setAfAi         ( Actor::DB.getAi         (_id) );
}

bool Actor::isAlive() const
{
  return  afDestrucible() && afDestrucible()->isAlive();
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
Container *Actor::afContainer() const
{
  return _afContainer;
}

void Actor::setAfContainer(Container *afContainer)
{
  _afContainer = afContainer;
  if (_afContainer)
    _afContainer->setOwner(this);
}
Pickable *Actor::afPickable() const
{
  return _afPickable;
}

void Actor::setAfPickable(Pickable *afPickable)
{
  _afPickable = afPickable;
  if (_afPickable)
    _afPickable->setOwner(this);
}
Destrucible *Actor::afDestrucible() const
{
  return _afDestrucible;
}

void Actor::setAfDestrucible(Destrucible *afDestrucible)
{
  _afDestrucible = afDestrucible;
  if (_afDestrucible)
    _afDestrucible->setOwner(this);
}
Attacker *Actor::afAttacker() const
{
  return _afAttacker;
}

void Actor::setAfAttacker(Attacker *afAttacker)
{
  _afAttacker = afAttacker;
  if (_afAttacker)
    _afAttacker->setOwner(this);
}
Ai *Actor::afAi() const
{
  return _afAi;
}

void Actor::setAfAi(Ai *afAi)
{
  _afAi = afAi;
  if (_afAi)
    _afAi->setOwner(this);
}


TCODColor Actor::getColor() const
{
  return Actor::DB.getColor(_id);;
}

unsigned char Actor::getChar() const
{
  return Actor::DB.getChar(_id);;
}
