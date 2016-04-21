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
#include <actor_descriptions.h>
#include <trap.h>
#include <skill.h>

namespace amarlon {

ActorPtr Actor::create(int aId, int x, int y, MapPtr map)
{
  ActorPtr actor = Engine::instance().getActorDB().fetch(aId);
  actor->setMap(map);
  actor->setPosition(x,y);
  actor->applyPassiveSkills();

  return actor;
}

ActorPtr Actor::create(ActorDescriptionPtr dsc, bool prototyped)
{
  ActorPtr actor;
  if ( dsc )
  {
    actor = prototyped ? create( *dsc->id)
                       : ActorPtr(new Actor);
    actor->upgrade(dsc);
  }
  return actor;
}

void Actor::applyPassiveSkills()
{
  CharacterPtr c = getFeature<Character>();
  if ( c )
  {
    for ( SkillPtr s : c->getSkills([](SkillPtr s){ return s->isPassive(); }))
    {
      //remove if already applied
      _effects->remove( [&](StatusEffectPtr se){
        return se->getScript() == s->getScript();
      }, false);

      //apply
      s->use( shared_from_this(), Target(shared_from_this()) );
    }
  }
}

void Actor::upgrade(ActorDescriptionPtr dsc)
{
  if ( dsc )
  {
    //Base fields
    if (dsc->id)           _id = *dsc->id;
    if (dsc->x)            _x = *(dsc->x);
    if (dsc->y)            _y = *(dsc->y);
    if (dsc->name)         _name = *(dsc->name);
    if (dsc->inscription)  _inscription = *(dsc->inscription);
    if (dsc->symbol)       _symbol = *(dsc->symbol);
    if (dsc->color)        _color = strToColor(*dsc->color);
    if (dsc->blocks)       _blocks = *(dsc->blocks);
    if (dsc->fovOnly)      _fovOnly = *(dsc->fovOnly);
    if (dsc->transparent)  _transparent = *(dsc->transparent);
    if (dsc->tilePriority) _priority = *(dsc->tilePriority);
    if (dsc->description)  _description = *(dsc->description);
    if (dsc->visible)      setVisible( *(dsc->visible) );

    //Features
    for (auto& f : dsc->features )
    {
      if ( f.second )
      {
        ActorFeature::Type f_type = static_cast<ActorFeature::Type>(f.first);
        auto it = _features.find( f_type );
        if ( it != _features.end() )
        {
          it->second->upgrade( f.second );
        }
        else
        {
          auto feat = ActorFeature::create( f_type, f.second);
          feat->setOwner( shared_from_this() );
          _features[ f_type ] = feat;
        }
      }
    }

    //Status Effects
    if ( !_effects ) _effects.reset( new StatusEffectsManager( shared_from_this()) );
    for ( auto e : dsc->statusEffects )
    {
      StatusEffectPtr se( new StatusEffect(e.name, e.script, e.duration));
      getStatusEffects().add( se );
    }

    applyPassiveSkills();
  }
}

ActorDescriptionPtr Actor::toDescriptionStruct()
{
  ActorDescriptionPtr dsc( new ActorDescription );
  ActorPtr base = Actor::create( _id );

  dsc->id = static_cast<int>( _id );
  dsc->x = _x;
  dsc->y = _y;
  if ( _fovOnly     != base->_fovOnly )     dsc->fovOnly = _fovOnly;
  if ( _transparent != base->_transparent ) dsc->transparent = _transparent;
  if ( _blocks      != base->_blocks )      dsc->blocks = _blocks;
  if ( _priority    != base->_priority )    dsc->tilePriority = _priority;
  if ( _color       != base->_color )       dsc->color = colorToStr(_color);
  if ( _symbol      != base->_symbol )      dsc->symbol = _symbol;
  if ( _name        != base->_name )        dsc->name = _name;
  if ( _inscription != base->_inscription ) dsc->inscription = _inscription;

  if ( isVisible()  != base->isVisible() )  dsc->visible = isVisible();
  if ( _description != base->_description ) dsc->description = _description;

  for ( StatusEffectPtr se : _effects->getEffects() )
  {
    StatusEffectDsc seDsc;
    seDsc.name     = se->getName();
    seDsc.script   = se->getScript();
    seDsc.duration = se->getDuration();

    dsc->statusEffects.push_back( seDsc );
  }

  for ( auto& kv : _features )
  {
    if ( kv.second )
    {
      DescriptionPtr fDsc = kv.second->toDescriptionStruct( base->getFeature(kv.first) );
      if ( fDsc ) dsc->features[ (int)kv.first ] = fDsc;
    }
  }

  return dsc;
}

Actor::Actor(int aId, int x, int y, MapPtr map)
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
  setVisible(true);
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

void Actor::morph(int newType)
{
  ActorPtr newActor = Engine::instance().getActorDB().fetch(newType);
  if ( newActor )
  {
    newActor->setPosition( getX(), getY() );
    *this = *newActor;    
  }
}

int Actor::update()
{
  int turns = 0;

  for ( auto afPair : _features )
  {
    if ( afPair.second )
      turns = std::max(turns, afPair.second->update());
  }

  _effects->tick();

  return turns;
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
    _inscription= rhs._inscription;
    _description = rhs._description;
    _color = rhs._color;
    _symbol = rhs._symbol;
    _flags = rhs._flags;

    _features.clear();
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
  equal &= rhs._inscription == _inscription;
  equal &= rhs._color == _color;
  equal &= rhs._symbol == _symbol;

  for ( auto af : _features)
  {
    ActorFeaturePtr feature = af.second;
    equal &= ( feature->isEqual( rhs.getFeature( feature->getType() ) ) );
  }

  return equal;
}


void Actor::setType(int newType)
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

bool Actor::sees(ActorPtr actor)
{
  //Check if actors are on the same map
  if ( _map.lock() != nullptr && _map.lock() == actor->getMap() )
  {
    //And are in player's field of viev and are visible
    return isInFov() && actor->isInFov() && isVisible();
  }
  return false;
}

bool Actor::isAllyOf(ActorPtr actor)
{
  if ( actor )
  {
    CharacterPtr me = getFeature<Character>();
    CharacterPtr he = actor->getFeature<Character>();
    if ( me && he )
    {
      return relations::get(me->getTeam(), he->getTeam())
          == relations::Ally;
    }
  }
  return false;
}

bool Actor::isHostileTo(ActorPtr actor)
{
  if ( actor )
  {
    CharacterPtr me = getFeature<Character>();
    CharacterPtr he = actor->getFeature<Character>();
    if ( me && he )
    {
      return relations::get(me->getTeam(), he->getTeam())
          == relations::Hostile;
    }
  }
  return false;
}

void Actor::interract(ActorPtr actor)
{
  TrapPtr trap = getFeature<Trap>();
  if ( trap && actor && actor->isAlive() )
  {
    trap->trigger( Target(actor) );
    if ( isInFov() ) trap->setDetected(true);
  }
}

StatusEffectsManager &Actor::getStatusEffects() const
{
  return *_effects;
}

void Actor::removeAllFeatures()
{
  _features.clear();
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

int Actor::getType() const
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

std::string Actor::getInscription() const
{
  return _inscription;
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

void Actor::setPosition(const Point &p)
{
  setPosition(p.x, p.y);
}

MapPtr Actor::getMap() const
{
  return _map.lock();
}

void Actor::setMap(MapPtr map)
{
  _map = map;
}

bool Actor::isVisible() const
{
  return _flags[0];
}

void Actor::setVisible(bool visible)
{
  _flags.set(0, visible);

  if ( visible && _effects )
  {
    getStatusEffects().remove( "Invisibility" );
  }
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

ActorActionResult Actor::performAction(ActorActionPtr action)
{
  AiPtr ai = getFeature<Ai>();
  return ai ? ai->performAction(action)
            : ActorActionResult::MissingAI;
}

ActorActionResult Actor::performAction(ActorAction *action)
{
  return performAction( ActorActionPtr(action) );
}

void Actor::render(TCODConsole *console)
{
  if ( getSymbol() != ' ' )
  {
    if ( !isVisible() )
    {
      console->setChar( getX(), getY(), getSymbol() );
      console->setCharForeground( getX(), getY(), getColor()*0.3 );
    }
    else
    {
      console->setChar( getX(), getY(), getSymbol() );
      console->setCharForeground( getX(), getY(), getColor() );
    }
  }


  TrapPtr trap = getFeature<Trap>();
  if ( trap && trap->isDetected() )
  {
    console->setCharBackground( getX(),
                                getY(),
                                trap->isArmed() ? TCODColor::red : TCODColor::desaturatedRed );
  }
}

bool Actor::isPlayerControlled() const
{
  bool r = false;

  AiPtr ai = getFeature<Ai>();
  if ( ai )
  {
    r = ai->getCurrentState() == FSMStateType::PLAYER_CONTROLLED;
  }

  return r;
}

std::string Actor::debug(const std::string& linebreak)
{
  std::string d;
  d += "======="+getName()+"=======" + linebreak;
  d += "IsAlive = "; d += (isAlive() ? "True"+linebreak : "False"+linebreak);
  d += "IsPlayerControlled = "; d += (isPlayerControlled() ? "True"+linebreak : "False"+linebreak);
  d += " " + linebreak + "~~~~~~~FEATURES~~~~~~~"+linebreak+" "+linebreak;
  for (auto f : _features)
  {
    if ( f.second ) d += f.second->debug(linebreak);
  }
  d += "########################"+linebreak;
  return d;
}

void Actor::printDebug()
{
  printf("%s",debug().c_str());
}

}

