#include "map_db.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <memory>
#include <map.h>
#include <actor_type.h>
#include <actor.h>

namespace amarlon {

using namespace rapidxml;
using namespace std;

MapDB::MapDB()
{
}

MapDB::~MapDB()
{
}

MapPtr MapDB::fetch(MapId id)
{
  MapPtr map;

  auto mIter = _maps.find(id);
  if ( mIter != _maps.end() )
  {
    map.reset( new Map(*mIter->second) );
  }

  return map;
}

bool MapDB::load(const string& fn)
{
  ifstream ifs(fn);

  if (ifs.is_open())
  {
    _maps.clear();

    MapsData maps;
    maps.ParseFromIstream(&ifs);

    for ( auto it = maps.map().begin(); it != maps.map().end(); ++it )
    {
      _maps[ static_cast<MapId>(it->id()) ] = MapPtr(new Map(*it));
    }

    return true;
  }
  return false;
}

bool MapDB::store(const string& fn)
{
  ofstream ofs(fn);
  if ( ofs.is_open() )
  {
    MapsData maps;

    for ( auto& kv : _maps )
      maps.add_map()->CopyFrom( kv.second->getData() );

    return maps.SerializeToOstream(&ofs);
  }
  return false;
}

}

