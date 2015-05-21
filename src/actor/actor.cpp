#include "actor.h"
#include "world/map.h"
#include <iostream>

namespace amarlon {

ActorDB Actor::DB;
ActorPtr Actor::Player(nullptr);
unsigned Actor::InstanceCounter = 0;

ActorPtr Actor::create(ActorType aId, int x, int y, MapPtr map)
{
  ActorPtr actor( new Actor(aId, x, y, map) );
  actor->init();

  return actor;
}

Actor::Actor(ActorType aId, int x, int y, MapPtr map)
  : _id(aId)
  , _x(x)
  , _y(y)
  , _map(map)
  , _instanceId( ++Actor::InstanceCounter )
{
}

void Actor::init()
{
  _features = Actor::DB.getAllFeatures(_id);
  for (auto f : _features)
  {
    f.second->setOwner( shared_from_this() );
  }
}

Actor::~Actor()
{
}

void Actor::move(int dx, int dy)
{
  MapPtr map = _map.lock();
  if ( map ) map->removeActor( shared_from_this() );

  _x += dx;
  _y += dy;

  if ( map ) map->addActor( shared_from_this() );
}

void Actor::morph(ActorType newType)
{
  _id = newType;

  _features.clear();
  _features = Actor::DB.getAllFeatures(_id);
  for (auto f : _features) f.second->setOwner( shared_from_this() );
}

ActorPtr Actor::clone()
{
  ActorPtr cloned( new Actor( getId(), getX(), getY() ) );

  for ( auto af : _features )
  {
    cloned->insertFeature( af.second->clone() );
  }

  return cloned;
}

bool Actor::isEqual(ActorPtr rhs)
{
  bool equal = (rhs != nullptr);

  if ( rhs )
  {
    equal &= ( getId() == rhs->getId() );
    equal &= ( getFeatureCount() == rhs->getFeatureCount() );

    for ( auto af : _features)
    {
      ActorFeaturePtr feature = af.second;
      equal &= ( feature->isEqual( rhs->getFeature( feature->getType() ) ) );
    }
  }

  return equal;
}

void Actor::changeType(ActorType newType)
{
  _id = newType;
}

bool Actor::isAlive() const
{
  const FighterPtr f = getFeature<Fighter>();
  return  f && f->isAlive();
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
  MapPtr map = _map.lock();
  if ( map ) map->removeActor( shared_from_this() );
  _x = x;
  if ( map ) map->addActor( shared_from_this() );
}
int Actor::getY() const
{
  return _y;
}

void Actor::setY(int y)
{
  MapPtr map = _map.lock();
  if ( map ) map->removeActor( shared_from_this() );
  _y = y;
  if ( map ) map->addActor( shared_from_this() );
}

MapPtr Actor::getMap() const
{
  return _map.lock();
}

void Actor::setMap(MapPtr map)
{
  _map = map;
}

TCODColor Actor::getColor() const
{
  return Actor::DB.getColor(_id);;
}

unsigned char Actor::getChar() const
{
  return Actor::DB.getChar(_id);;
}

ActorFeaturePtr Actor::getFeature(ActorFeature::Type afType) const
{
  auto it = _features.find( afType );
  ActorFeaturePtr feature = it != _features.end() ? it->second : nullptr;

  return feature;
}

ActorFeaturePtr Actor::insertFeature(ActorFeaturePtr feature)
{
  ActorFeaturePtr overwriten;
  if ( feature != nullptr )
  {
    feature->setOwner( shared_from_this() );

    auto it = _features.find( feature->getType() );
    if ( it != _features.end() )
    {
      overwriten = it->second;
      it->second = feature;
    }
    else
    {
      _features[ feature->getType() ] = ActorFeaturePtr(feature);
    }
  }
  return overwriten;
}

size_t Actor::getFeatureCount() const
{
  return _features.size();
}
unsigned Actor::getInstanceId() const
{
    return _instanceId;
}

}
