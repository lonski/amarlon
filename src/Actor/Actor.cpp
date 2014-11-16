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
{
  _features = Actor::DB.getAllFeatures(aId);
  for (auto f : _features) f.second->setOwner(this);
}

Actor::~Actor()
{
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

  _features.clear();
  _features = Actor::DB.getAllFeatures(_id);
  for (auto f : _features) f.second->setOwner(this);
}

Actor *Actor::clone()
{
  Actor* cloned = new Actor( getId(), getX(), getY() );

  for ( auto af : _features )
  {
    cloned->insertFeature( af.second->clone() );
  }

  return cloned;
}

bool Actor::isEqual(Actor *rhs)
{
  bool equal = rhs != nullptr;

  if ( rhs != nullptr )
  {
    equal &= ( getId() == rhs->getId() );
    equal &= ( getFeatureCount() == rhs->getFeatureCount() );

    for ( auto af : _features)
    {
      ActorFeature* feature = af.second.get();
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
  const Fighter* f = getFeature<Fighter>();
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

TCODColor Actor::getColor() const
{
  return Actor::DB.getColor(_id);;
}

unsigned char Actor::getChar() const
{
  return Actor::DB.getChar(_id);;
}

ActorFeature *Actor::getFeature(ActorFeature::Type afType) const
{
  auto it = _features.find( afType );
  ActorFeature* feature = it != _features.end() ? it->second.get() : nullptr;

  return feature;
}

ActorFeaturePtr Actor::insertFeature(ActorFeature *feature)
{
  ActorFeaturePtr overwriten;
  if ( feature != nullptr )
  {
    feature->setOwner(this);

    auto it = _features.find( feature->getType() );
    if ( it != _features.end() )
    {
      overwriten = it->second;
      it->second.reset( feature );
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

}
