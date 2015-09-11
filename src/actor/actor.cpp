#include "actor.h"
#include <map.h>
#include <iostream>
#include <actor_action.h>
#include <utils.h>
#include <tile.h>
#include <engine.h>

namespace amarlon {

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
  _features = Engine::instance().getActorDB().getAllFeatures(_id);
  for (auto f : _features)
  {
    f.second->setOwner( shared_from_this() );
  }
}

Actor::~Actor()
{
}

void Actor::morph(ActorType newType)
{
  _id = newType;

  _features.clear();
  _features = Engine::instance().getActorDB().getAllFeatures(_id);
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
bool Actor::operator==(const Actor &rhs)
{
  bool equal = true;

  equal &= ( getId() == rhs.getId() );
  equal &= ( getFeatureCount() == rhs.getFeatureCount() );

  for ( auto af : _features)
  {
    ActorFeaturePtr feature = af.second;
    equal &= ( feature->isEqual( rhs.getFeature( feature->getType() ) ) );
  }

  return equal;
}

void Actor::changeType(ActorType newType)
{
  _id = newType;
}

bool Actor::isAlive() const
{
  const CharacterPtr f = getFeature<Character>();
  return  f && f->isAlive();
}

bool Actor::isFovOnly() const
{
  return Engine::instance().getActorDB().isFovOnly(_id);
}

bool Actor::isTransparent() const
{
  return Engine::instance().getActorDB().isTransparent(_id);
}

bool Actor::blocks() const
{
  return Engine::instance().getActorDB().blocks(_id);;
}

int Actor::getTileRenderPriority() const
{
  int priority = Engine::instance().getActorDB().getTileRenderPriority(_id);

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
  return Engine::instance().getActorDB().getName(_id);;
}

std::string Actor::getDescription()
{
  std::string str  = colorToStr(TCODColor::darkRed, true) + getName() + "\n \n";

  str += Engine::instance().getActorDB().getDescription(_id) + "\n \n";

  for ( auto& fPair : _features )
  {
    str += fPair.second->getDescription();
  }

  return str;
}

int Actor::getX() const
{
  return _x;
}

int Actor::getY() const
{
  return _y;
}

void Actor::setPosition(int x, int y)
{
  MapPtr map = _map.lock();
  if ( map ) map->removeActor( shared_from_this() );

  _x = x;
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
  return Engine::instance().getActorDB().getColor(_id);;
}

unsigned char Actor::getChar() const
{
  return Engine::instance().getActorDB().getChar(_id);;
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

const FeatureMap Actor::getFeatures() const
{
  return _features;
}
unsigned Actor::getInstanceId() const
{
  return _instanceId;
}

bool Actor::performAction(ActorActionPtr action)
{
  return action ? action->perform( shared_from_this() ) : false;
}

}
