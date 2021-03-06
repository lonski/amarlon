#ifndef ACTORSDATABASE_H
#define ACTORSDATABASE_H
#include <string>
#include <actor_descriptions.h>

namespace amarlon { namespace map_editor {

class ActorsDatabase
{
public:
  ActorsDatabase();

  ActorDescriptionPtr fetch(int id);
  void load(const std::string& fn);
  void loadPlugin(const std::string& fn);
  std::map<int, ActorDescriptionPtr> getActors() const;


private:
  std::map<int, ActorDescriptionPtr> _actors;
  void parse(std::vector<char> buffer);

};

}}

#endif // ACTORSDATABASE_H
