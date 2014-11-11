#include "Actor.h"
#include <world/map.h>

namespace amarlon {

ActorDB Actor::DB;
Actor* Actor::Player(nullptr);

Actor::Actor(ActorType aId, int x, int y, Map *map)
  : _id(aId)
  , _x(x)
  , _y(y)
  , _map(map)
  , _afContainer(nullptr)
  , _afPickable(nullptr)
  , _afFighter(nullptr)
  , _afAi(nullptr)
  , _afOpenable(nullptr)
  , _afWearer(nullptr)  
{  
  setAfContainer  ( Actor::DB.getContainer  (aId) );
  setAfPickable   ( Actor::DB.getPickable   (aId) );  
  setAfFighter    ( Actor::DB.getFighter    (aId) );
  setAfAi         ( Actor::DB.getAi         (aId) );
  setAfOpenable   ( Actor::DB.getOpenable   (aId) );
  setAfWearer     ( Actor::DB.getWearer     (aId) );
}

Actor::~Actor()
{
  delete _afAi;
  delete _afContainer;
  delete _afFighter;
  delete _afOpenable;
  delete _afPickable;
  delete _afWearer;

  _afAi = nullptr;
  _afContainer = nullptr;
  _afFighter = nullptr;
  _afOpenable = nullptr;
  _afPickable = nullptr;
  _afWearer = nullptr;
}

void Actor::move(int dx, int dy)
{
  if ( _map ) _map->removeActor( this );

  _x += dx;
  _y += dy;

  if ( _map ) _map->addActor( this );
}

void Actor::morph(ActorType newType)
{
  _id = newType;

  setAfContainer( Actor::DB.getContainer(_id) );
  setAfPickable ( Actor::DB.getPickable (_id) );
  setAfFighter  ( Actor::DB.getFighter  (_id) );
  setAfAi       ( Actor::DB.getAi       (_id) );
  setAfOpenable ( Actor::DB.getOpenable (_id) );
  setAfWearer   ( Actor::DB.getWearer   (_id) );
}

Actor *Actor::clone()
{
  Actor* cloned = new Actor( getId(), getX(), getY() );

  cloned->setAfContainer( dynamic_cast<Container*>( _afContainer ? _afContainer->clone() : nullptr ) );
  cloned->setAfPickable ( dynamic_cast<Pickable*> ( _afPickable  ? _afPickable->clone()  : nullptr ) );
  cloned->setAfOpenable ( dynamic_cast<Openable*> ( _afOpenable  ? _afOpenable->clone()  : nullptr ) );
  cloned->setAfFighter  ( dynamic_cast<Fighter*>  ( _afFighter   ? _afFighter->clone()   : nullptr ) );
  cloned->setAfAi       ( dynamic_cast<Ai*>       ( _afAi        ? _afAi->clone()        : nullptr ) );
  cloned->setAfWearer   ( dynamic_cast<Wearer*>   ( _afWearer    ? _afWearer->clone()    : nullptr ) );

  return cloned;
}

bool Actor::isEqual(Actor *rhs)
{
  bool equal = rhs != nullptr && ( getId() == rhs->getId() );

  if (equal)
  {
    if ( afContainer() ) equal &= afContainer()->isEqual( rhs->afContainer() );
    if ( afOpenable() ) equal &= afOpenable()->isEqual( rhs->afOpenable() );
    if ( afPickable() ) equal &= afPickable()->isEqual( rhs->afPickable() );
    if ( afFighter() ) equal &= afFighter()->isEqual( rhs->afFighter() );
    if ( afAi() ) equal &= afAi()->isEqual( rhs->afAi() );
    if ( afWearer() ) equal &= afWearer()->isEqual( rhs->afWearer() );
  }

  return equal;
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

int Actor::getTileRenderPriority() const
{
  int priority = Actor::DB.getTileRenderPriority(_id);

  //not set in xml, neither default value defined in ActorDB
  if ( priority == -1 )
  {
    priority = isAlive() ? Tile::defaultMonsterRenderPriority
                         : Tile::defaultItemRenderPriority;
  }

  return priority;
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
  if ( _map ) _map->removeActor( this );
  _x = x;
  if ( _map ) _map->addActor( this );
}
int Actor::getY() const
{
  return _y;
}

void Actor::setY(int y)
{
  if ( _map ) _map->removeActor( this );
  _y = y;
  if ( _map ) _map->addActor( this );
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

Wearer *Actor::afWearer() const
{
  return _afWearer;
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

void Actor::setAfWearer(Wearer *afWearer)
{
  delete _afWearer;
  _afWearer = afWearer;

  if (_afWearer)
    _afWearer->setOwner(this);
}


TCODColor Actor::getColor() const
{
  return Actor::DB.getColor(_id);;
}

unsigned char Actor::getChar() const
{
  return Actor::DB.getChar(_id);;
}

}
