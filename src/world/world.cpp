#include "world.h"
#include <map.h>
#include <vector>
#include <fstream>
#include <actor.h>
#include <map.pb.h>

using namespace rapidxml;

namespace amarlon {

World::World(const std::string& mapsFile)
  : _currentMap(MapId::Null)
  , _mapDB( new MapDB )
{
  _mapDB->load( mapsFile );
}

World::~World()
{
}

MapPtr World::getCurrentMap()
{
  return fetch(_currentMap);
}

MapPtr World::fetch(MapId id)
{
  MapPtr map;

  auto mIter = _maps.find(id);
  if ( mIter != _maps.end() )
  {
    map = mIter->second;
  }
  else
  {
    map = _mapDB->fetch(id);
    _maps.insert( std::make_pair(id, map) );
  }

  return map;
}

void World::changeMap(MapId id)
{
  _currentMap = id;
}

const ActorPtr World::getPlayer()
{
  return _player;
}

void World::setPlayer(ActorPtr player)
{
  if ( player )
  {
    if ( _player ) getCurrentMap()->removeActor( _player );
    _player = player;
    getCurrentMap()->addActor( _player );
  }
  else throw std::logic_error("Cant set null player!");
}

bool World::store(const std::string &fn)
{
  std::ofstream ofs(fn, std::ios_base::app | std::ios_base::out);
  if ( ofs.is_open() )
  {
    getCurrentMap()->removeActor( getPlayer() );

    WorldData world;

    for ( auto& kv : _maps )
      world.mutable_map()->Add()->CopyFrom( kv.second->getData() );

    world.mutable_player()->CopyFrom(_player->getData());
    world.set_current_map(static_cast<int>(_currentMap));

    //put back player
    getCurrentMap()->addActor( getPlayer() );

    return world.SerializeToOstream(&ofs);
  }
  return false;
}

bool World::load(const std::string& fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    WorldData world;
    world.ParseFromIstream(&ifs);

    //Load maps
    for ( auto it = world.map().begin(); it != world.map().end(); ++it )
    {
      _maps[ static_cast<MapId>(it->id()) ] = MapPtr(new Map(*it));
    }

    //Set current map
    _currentMap = static_cast<MapId>(world.current_map());

    //Load player
    _player = Actor::create(world.player());
    getCurrentMap()->addActor( _player );

    return true;
  }
  return false;
}

}

