#ifndef ACTORDB_H
#define ACTORDB_H

#include <string>
#include <map>
#include <memory>
#include <actor_type.h>
#include <actor.pb.h>

namespace amarlon {

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

class ActorDB
{
public:
  ActorDB();

  ActorPtr fetch(ActorType type);
  ActorData fetchData(ActorType type);

  /**
   * @brief loads given file, parses xml and creates actor descriptions
   * @param path to file to be loaded
   */
  bool load(const std::string& fn);

private:
  std::map<ActorType, ActorData> _actors;

};

}
#endif // ACTORDB_H
