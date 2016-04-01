#include "actor_db.h"
#include <fstream>
#include <algorithm>
#include <utils.h>
#include <actor_descriptions.h>
#include <actor.h>

namespace amarlon {

using namespace std;

ActorDB::ActorDB()
{
}

ActorPtr ActorDB::fetch(ActorType type)
{
  return Actor::create( fetchData(type) );
}

ActorData ActorDB::fetchData(ActorType type)
{
  auto it = _actors.find(type);
  return it != _actors.end() ? it->second : ActorData();
}

bool ActorDB::load(const string &fn)
{
  std::ifstream ifs(fn);
  if ( ifs.is_open() )
  {
    _actors.clear();

    ActorsData actors;
    actors.ParseFromIstream(&ifs);

    for ( auto it = actors.actor().begin(); it != actors.actor().end(); ++it )
    {
      _actors[ static_cast<ActorType>(it->actor_type()) ] = *it;
    }

    return true;
  }
  return false;
}

}

