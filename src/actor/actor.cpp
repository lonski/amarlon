#include "actor.h"
#include <map.h>
#include <iostream>
#include <actor_action.h>
#include <utils.h>
#include <tile.h>
#include <engine.h>
#include <actor_db.h>
#include <messenger.h>
#include <status_effects_manager.h>
#include <world.h>
#include <monster_ai.h>

namespace amarlon {

ActorPtr Actor::create(ActorType aId, int x, int y, MapPtr map)
{
  ActorPtr actor = Engine::instance().getActorDB().fetch(aId);
  actor->setMap(map);
  actor->setPosition(x,y);

  return actor;
}

Actor::Actor(ActorType aId, int x, int y, MapPtr map)
  : _id(aId)
  , _x(x)
  , _y(y)
  , _map(map)
{
  addObserver( &Engine::instance().getMessenger() );
}

Actor::~Actor()
{
}

void Actor::morph(ActorType newType)
{
  Engine::instance().getActorDB().morph(shared_from_this(), newType);
}

void Actor::update()
{
  AiPtr ai = getFeature<Ai>();
  if ( ai )
  {
    ai->update();
  }

  _effects->tick();
}

ActorPtr Actor::clone()
{
  ActorPtr cloned( new Actor( getType(), getX(), getY() ) );

  for ( auto af : _features )
  {
    cloned->insertFeature( af.second->clone() );
  }

  cloned->_effects = _effects->clone();

  return cloned;
}
bool Actor::operator==(const Actor &rhs) const
{
  bool equal = true;

  equal &= ( getType() == rhs.getType() );
  equal &= ( _features.size() == rhs._features.size() );

  for ( auto af : _features)
  {
    ActorFeaturePtr feature = af.second;
    equal &= ( feature->isEqual( rhs.getFeature( feature->getType() ) ) );
  }

  return equal;
}

void Actor::setType(ActorType newType)
{
  _id = newType;
}

bool Actor::isAlive() const
{
  const CharacterPtr f = getFeature<Character>();
  return  f && f->isAlive();
}

bool Actor::isInFov()
{
  MapPtr cMap = Engine::instance().getWorld().getCurrentMap();
  if ( cMap )
  {
    return cMap->isInFov( getX(), getY() );
  }
  return false;
}

bool Actor::isAllyOf(ActorPtr actor)
{
  //a temporary stub
  //only monsters are allies between them
  //TODO real implementation
  bool isAlly = false;

  if ( this != actor.get() )
  {
    if ( isAlive() )
    {
      MonsterAiPtr thisAi = std::dynamic_pointer_cast<MonsterAi>(getFeature<Ai>());
      MonsterAiPtr actorAi = std::dynamic_pointer_cast<MonsterAi>(actor->getFeature<Ai>());
      isAlly = (thisAi != nullptr && actorAi != nullptr);
    }
  }
  else
  {
    isAlly = true;
  }

  return isAlly;
}

StatusEffectsManager &Actor::getStatusEffects() const
{
  return *_effects;
}

bool Actor::isFovOnly() const
{
  return Engine::instance().getActorDB().isFovOnly(_id);
}

bool Actor::isTransparent() const
{
  return Engine::instance().getActorDB().isTransparent(_id);
}

bool Actor::isBlocking() const
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

ActorType Actor::getType() const
{
  return _id;
}

std::string Actor::getName() const
{
  return Engine::instance().getActorDB().getName(_id);;
}

std::string Actor::getDescription()
{
  std::string str  = colorToStr(TCODColor::darkRed, true) + getName() + "# #";

  str += Engine::instance().getActorDB().getDescription(_id) + "# #";

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

bool Actor::performAction(ActorActionPtr action)
{
  return action ? action->perform( shared_from_this() ) : false;
}

}

