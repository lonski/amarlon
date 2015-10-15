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
#include <status_effect.h>
#include <world.h>
#include <monster_ai.h>
#include <actor_descriptions.h>

namespace amarlon {

ActorPtr Actor::create(ActorType aId, int x, int y, MapPtr map)
{
  ActorPtr actor = Engine::instance().getActorDB().fetch(aId);
  actor->setMap(map);
  actor->setPosition(x,y);

  return actor;
}

ActorPtr Actor::create(ActorDescriptionPtr dsc, bool prototyped)
{
  ActorPtr actor;
  if ( dsc )
  {
    actor = prototyped ? create(dsc->id) : ActorPtr(new Actor);
    actor->deserialize(dsc);
  }
  return actor;
}

void Actor::deserialize(ActorDescriptionPtr dsc)
{
  if ( dsc )
  {
    //Base fields
    _id = dsc->id;

    if (dsc->x)            _x = *(dsc->x);
    if (dsc->y)            _y = *(dsc->y);
    if (dsc->name)         _name = *(dsc->name);
    if (dsc->symbol)       _symbol = *(dsc->symbol);
    if (dsc->color)        _color = *(dsc->color);
    if (dsc->blocks)       _blocks = *(dsc->blocks);
    if (dsc->fovOnly)      _fovOnly = *(dsc->fovOnly);
    if (dsc->transparent)  _transparent = *(dsc->transparent);
    if (dsc->tilePriority) _priority = *(dsc->tilePriority);
    if (dsc->description)  _description = *(dsc->description);

    //Status Effects
    _effects.reset( new StatusEffectsManager( shared_from_this() ) );
    for ( auto e : dsc->statusEffects )
    {
      StatusEffectPtr se( new StatusEffect(static_cast<SpellId>(e.spellId), e.duration));
      getStatusEffects().add( se );
    }

    //Features
    if ( dsc->pickable )    _features[ActorFeature::PICKABLE]    = ActorFeature::create(ActorFeature::PICKABLE, dsc->pickable);
    if ( dsc->character )   _features[ActorFeature::CHARACTER]   = ActorFeature::create(ActorFeature::CHARACTER, dsc->character);
    if ( dsc->ai )          _features[ActorFeature::AI]          = ActorFeature::create(ActorFeature::AI, dsc->ai);
    if ( dsc->openable )    _features[ActorFeature::OPENABLE]    = ActorFeature::create(ActorFeature::OPENABLE, dsc->openable);
    if ( dsc->wearer )      _features[ActorFeature::WEARER]      = ActorFeature::create(ActorFeature::WEARER, dsc->wearer);
    if ( dsc->inventory )   _features[ActorFeature::INVENTORY]   = ActorFeature::create(ActorFeature::INVENTORY, dsc->inventory);
    if ( dsc->destroyable ) _features[ActorFeature::DESTROYABLE] = ActorFeature::create(ActorFeature::DESTROYABLE, dsc->destroyable);

    for (auto f : _features)
    {
      f.second->setOwner( shared_from_this() );
    }
  }
}

Actor::Actor(ActorType aId, int x, int y, MapPtr map)
  : _id(aId)
  , _x(x)
  , _y(y)
  , _map(map)
  , _fovOnly(true)
  , _transparent(false)
  , _blocks(false)
  , _priority( -1 )
  , _color(TCODColor::white)
  , _symbol('#')
{
  addObserver( &Engine::instance().getMessenger() );
}

Actor::Actor(const Actor &a)
  : enable_shared_from_this(a)
{
  *this = a;
}

Actor::~Actor()
{
}

void Actor::morph(ActorType newType)
{
  ActorPtr newActor = Engine::instance().getActorDB().fetch(newType);
  if ( newActor )
  {
    *this = *newActor;
  }
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
  ActorPtr cloned( new Actor );
  *cloned = *this;

  return cloned;
}

Actor& Actor::operator=(const Actor &rhs)
{
  if ( this != &rhs )
  {
    _id = rhs._id;
    _x = rhs._x;
    _y = rhs._y;
    _map = rhs._map;
    _fovOnly = rhs._fovOnly;
    _transparent = rhs._transparent;
    _blocks = rhs._blocks;
    _priority = rhs._priority;
    _name = rhs._name;
    _description = rhs._description;
    _color = rhs._color;
    _symbol = rhs._symbol;

    for ( auto af : rhs._features )
    {
      insertFeature( af.second->clone() );
    }

    _effects = rhs._effects->clone();
  }

  return *this;
}

bool Actor::operator==(const Actor &rhs) const
{
  bool equal = true;

  equal &= ( getType() == rhs.getType() );
  equal &= ( _features.size() == rhs._features.size() );

  equal &= rhs._fovOnly == _fovOnly;
  equal &= rhs._transparent == _transparent;
  equal &= rhs._blocks == _blocks;
  equal &= rhs._priority == _priority;
  equal &= rhs._name == _name;
  equal &= rhs._description == _description;
  equal &= rhs._color == _color;
  equal &= rhs._symbol == _symbol;

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
  return _fovOnly;
}

void Actor::setFovOnly(bool f)
{
  _fovOnly = f;
}

bool Actor::isTransparent() const
{
  return _transparent;
}

void Actor::setTransparent(bool t)
{
  _transparent = t;
}

bool Actor::isBlocking() const
{
  return _blocks;
}

void Actor::setBlocking(bool b)
{
  _blocks = b;
}

int Actor::getTileRenderPriority() const
{
  int p = _priority;

  if ( p == -1 )
  {
    p = isAlive() ? Tile::defaultMonsterRenderPriority
                  : Tile::defaultItemRenderPriority;
  }

  return p;
}

ActorType Actor::getType() const
{
  return _id;
}

std::string Actor::getName() const
{
  return _name;
}

void Actor::setName(std::string n)
{
  _name = n;
}

std::string Actor::getDescription()
{
  std::string str  = colorToStr(TCODColor::darkRed, true) + getName() + "# #";

  str += _description + "# #";

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
  return _color;
}

void Actor::setColor(TCODColor c)
{
  _color = c;
}

unsigned char Actor::getSymbol() const
{
  return _symbol;
}

void Actor::setSymbol(unsigned char s)
{
  _symbol = s;
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

