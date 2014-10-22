#include "Actor.h"
#include "World/Map.h"
#include <iostream>

#define private public
#include "Actor/Effects/SelfHealEffect.h"

ActorDB Actor::DB;
Actor* Actor::Player(nullptr);

Actor::Actor(ActorType aId, int x, int y)
  : _id(aId)
  , _x(x)
  , _y(y)
  , _afContainer(nullptr)
  , _afPickable(nullptr)
  , _afFighter(nullptr)
  , _afAi(nullptr)
  , _afOpenable(nullptr)
{  
  setAfContainer  ( Actor::DB.getContainer  (aId) );
  setAfPickable   ( Actor::DB.getPickable   (aId) );  
  setAfFighter    ( Actor::DB.getFighter    (aId) );
  setAfAi         ( Actor::DB.getAi         (aId) );
  setAfOpenable   ( Actor::DB.getOpenable   (aId) );
}

void Actor::move(int dx, int dy)
{
  _x += dx;
  _y += dy;
}

void Actor::morph(ActorType newType)
{
  _id = newType;

  setAfContainer( Actor::DB.getContainer(_id) );
  setAfPickable ( Actor::DB.getPickable (_id) );
  setAfFighter  ( Actor::DB.getFighter  (_id) );
  setAfAi       ( Actor::DB.getAi       (_id) );
  setAfOpenable ( Actor::DB.getOpenable (_id) );
}

Actor *Actor::clone()
{
  Actor* cloned = new Actor( getId(), getX(), getY() );

  cloned->setAfContainer( dynamic_cast<Container*>( _afContainer ? _afContainer->clone() : nullptr ) );
  cloned->setAfPickable ( dynamic_cast<Pickable*> ( _afPickable  ? _afPickable->clone()  : nullptr ) );
  cloned->setAfOpenable ( dynamic_cast<Openable*> ( _afOpenable  ? _afOpenable->clone()  : nullptr ) );
  cloned->setAfFighter  ( dynamic_cast<Fighter*>  ( _afFighter   ? _afFighter->clone()   : nullptr ) );
  cloned->setAfAi       ( dynamic_cast<Ai*>       ( _afAi        ? _afAi->clone()        : nullptr ) );

  return cloned;
}

void Actor::changeType(ActorType newType)
{
  _id = newType;
}

bool Actor::isAlive() const
{
  return  afFighter() && afFighter()->isAlive();
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
  delete _afContainer;
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
  delete _afPickable;
  _afPickable = afPickable;

  if (_afPickable)
    _afPickable->setOwner(this);

}

Fighter *Actor::afFighter() const
{
  return _afFighter;
}

void Actor::setAfFighter(Fighter *afFighter)
{
  delete _afFighter;
  _afFighter = afFighter;

  if (_afFighter)
    _afFighter->setOwner(this);
}

Ai *Actor::afAi() const
{
  return _afAi;
}

Openable *Actor::afOpenable() const
{
  return _afOpenable;
}

void Actor::setAfAi(Ai *afAi)
{
  delete _afAi;
  _afAi = afAi;

  if (_afAi)
    _afAi->setOwner(this);
}

void Actor::setAfOpenable(Openable *afOpenable)
{
  delete _afOpenable;
  _afOpenable = afOpenable;

  if (_afOpenable)
    _afOpenable->setOwner(this);
}


TCODColor Actor::getColor() const
{
  return Actor::DB.getColor(_id);;
}

unsigned char Actor::getChar() const
{
  return Actor::DB.getChar(_id);;
}
