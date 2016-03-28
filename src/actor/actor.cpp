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

/* Flag bits */
const int ACTOR_INVISIBLE_BIT = 0;

ActorPtr Actor::create(const ActorData& data)
{
  ActorPtr actor( new Actor(data) );
  actor->initialize();

  return actor;
}

ActorPtr Actor::create(ActorType type)
{
  //TODO fetch from DB
  return nullptr;
}

void Actor::initialize()
{
  //initialize actor features
  if ( _data.has_ai() )          insertFeature( Ai::create(_data.ai()) );
  if ( _data.has_character() )   insertFeature( Character::create(_data.character()) );
  if ( _data.has_destroyable() ) insertFeature( Destroyable::create(_data.destroyable()) );
  if ( _data.has_inventory() )   insertFeature( Inventory::create(_data.inventory()) );
  if ( _data.has_openable() )    insertFeature( Openable::create(_data.openable()) );
  if ( _data.has_pickable() )    insertFeature( Pickable::create(_data.pickable()) );
  if ( _data.has_trap() )        insertFeature( Trap::create(_data.trap()) );
  if ( _data.has_wearer() )      insertFeature( Wearer::create(_data.wearer()) );
  if ( _data.has_talker() )      insertFeature( Talker::create(_data.talker()) );

  //initialize status effects
  _effects.reset( new StatusEffectsManager(shared_from_this()) );
  for ( auto se = _data.effects().begin(); se != _data.effects().end(); ++se)
    getStatusEffects().add( StatusEffectPtr(new StatusEffect(*se)) );

  applyPassiveSkills();

  addObserver( &Engine::instance().getMessenger() );
}

void Actor::applyPassiveSkills()
{
  CharacterPtr c = getFeature<Character>();
  if ( c )
  {
    for ( SkillPtr s : c->getSkills([](SkillPtr s){ return s->isPassive(); }))
    {
      //remove if already applied
      getStatusEffects().remove( [&](StatusEffectPtr se){
        return se->getScript() == s->getScript();
      }, false);

      //apply
      s->use( shared_from_this(), Target(shared_from_this()) );
    }
  }
}

Actor::Actor(const ActorData &data)
{
  _data.CopyFrom(data);
}

Actor::~Actor()
{
}

ActorPtr Actor::clone() const
{
  ActorPtr cloned( new Actor(*this) );
  cloned->initialize();

  return cloned;
}

Actor::Actor(const Actor &a)
  : enable_shared_from_this(a)
{
  *this = a;
}

Actor& Actor::operator=(const Actor &rhs)
{
  if ( this != &rhs )
  {
    rhs.updataData();
    _data.CopyFrom(rhs._data);
    _map = rhs._map;
  }

  return *this;
}

bool Actor::operator==(const Actor &rhs) const
{
  rhs.updataData();
  updataData();

  return _data.SerializeAsString() == rhs._data.SerializeAsString();
}

void Actor::updataData() const
{
  //Update Actor Feature Data
  for ( auto kv : _features )
  {
    if ( kv.second )
    {
      switch ( kv.first )
      {
        case ActorFeature::AI:          _data.mutable_ai()         ->CopyFrom( kv.second->getDataPolymorphic() ); break;
        case ActorFeature::OPENABLE:    _data.mutable_openable()   ->CopyFrom( kv.second->getDataPolymorphic() ); break;
        case ActorFeature::WEARER:      _data.mutable_wearer()     ->CopyFrom( kv.second->getDataPolymorphic() ); break;
        case ActorFeature::INVENTORY:   _data.mutable_inventory()  ->CopyFrom( kv.second->getDataPolymorphic() ); break;
        case ActorFeature::CHARACTER:   _data.mutable_character()  ->CopyFrom( kv.second->getDataPolymorphic() ); break;
        case ActorFeature::PICKABLE:    _data.mutable_pickable()   ->CopyFrom( kv.second->getDataPolymorphic() ); break;
        case ActorFeature::DESTROYABLE: _data.mutable_destroyable()->CopyFrom( kv.second->getDataPolymorphic() ); break;
        case ActorFeature::TRAP:        _data.mutable_trap()       ->CopyFrom( kv.second->getDataPolymorphic() ); break;
        case ActorFeature::TALKER:      _data.mutable_talker()     ->CopyFrom( kv.second->getDataPolymorphic() ); break;
        default:;
      }
    }
  }

  //Update Status Effects Data
  auto* effects_data = _data.mutable_effects();
  effects_data->Clear();
  for ( auto se : getStatusEffects().getEffects() )
    effects_data->Add()->CopyFrom( se->getData() );

}

void Actor::morph(ActorType newType)
{
  ActorPtr newActor = Actor::create(newType);
  if ( newActor )
  {
    newActor->setPosition( getX(), getY() );
    *this = *newActor;    
    initialize();
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


const ActorData& Actor::getData() const
{
  return _data;
}

void Actor::setType(ActorType newType)
{
  _data.set_actor_type( static_cast<int>(newType) );
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
  //TODO mby move 'interract' to feature and iterate over them
  TrapPtr trap = getFeature<Trap>();
  if ( trap && actor && actor->isAlive() )
  {
    trap->trigger( Target(actor) );
    if ( isInFov() ) trap->setDetected(true);
  }
}

StatusEffectsManager& Actor::getStatusEffects() const
{
  return *_effects;
}

bool Actor::isFovOnly() const
{
  return _data.is_fov_only();
}

void Actor::setFovOnly(bool f)
{
  _data.set_is_fov_only(f);
}

bool Actor::isTransparent() const
{
  return _data.is_transparent();
}

void Actor::setTransparent(bool t)
{
  _data.set_is_transparent(t);
}

bool Actor::isBlocking() const
{
  return _data.is_blocking();
}

void Actor::setBlocking(bool b)
{
  _data.set_is_blocking(b);
}

int Actor::getTileRenderPriority() const
{
  int p = _data.render_priority();

  if ( p == -1 )
  {
    p = isAlive() ? Tile::defaultMonsterRenderPriority
                  : Tile::defaultItemRenderPriority;
  }

  return p;
}

ActorType Actor::getType() const
{
  return static_cast<ActorType>(_data.actor_type());
}

std::string Actor::getName() const
{
  return _data.name();
}

void Actor::setName(std::string n)
{
  _data.set_name(n);
}

std::string Actor::getDescription()
{
  std::string str  = colorToStr(TCODColor::darkRed, true) + getName() + "# #";

  str += _data.description() + "# #";

  for ( auto& fPair : _features )
  {
    str += fPair.second->getDescription();
  }

  return str;
}

int Actor::getX() const
{
  return _data.x();
}

int Actor::getY() const
{
  return _data.y();
}

void Actor::setPosition(int x, int y)
{
  MapPtr map = _map.lock();
  if ( map ) map->removeActor( shared_from_this() );

  _data.set_x(x);
  _data.set_y(y);

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
  ::google::protobuf::uint32 f = _data.flags();
  return !isBitSet(f, ACTOR_INVISIBLE_BIT);
}

void Actor::setVisible(bool visible)
{
  ::google::protobuf::uint32 f = _data.flags();
  setBit(f, ACTOR_INVISIBLE_BIT, !visible);
  _data.set_flags(f);

  if ( visible ) getStatusEffects().remove( "Invisibility" );
}

TCODColor Actor::getColor() const
{
  return strToColor(_data.color());
}

void Actor::setColor(TCODColor c)
{
  _data.set_color(colorToStr(c));
}

unsigned char Actor::getSymbol() const
{
  return _data.symbol().front();
}

void Actor::setSymbol(unsigned char s)
{
  _data.set_symbol( std::string(1, s) );
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
    feature->setOwner( shared_from_this() ); //TODO cannot call it from constructor!

    auto it = _features.find( feature->getFeatureType() );
    if ( it != _features.end() )
    {
      overwriten = it->second;
      it->second = feature;
    }
    else
    {
      _features[ feature->getFeatureType() ] = ActorFeaturePtr(feature);
    }
  }
  return overwriten;
}

ActorActionResult Actor::performAction(ActorActionPtr action)
{
  AiPtr ai = getFeature<Ai>();
  return ai ? ai->performAction(action)
            : ActorActionResult::Nok;
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

