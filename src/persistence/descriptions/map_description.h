#ifndef MAP_DESCRIPTION
#define MAP_DESCRIPTION

#include <vector>
#include <map>
#include <memory>
#include <description.h>
#include <actor_action_description.h>

namespace amarlon {

struct ActorDescription;
typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;

struct MapDescription : Description
{
  int id;
  int width;
  int height;
  std::string binaryTiles;
  std::vector<ActorDescriptionPtr> actors;
  std::map<int /*direction*/, DescriptionPtr> actions;
};

typedef std::shared_ptr<MapDescription> MapDescriptionPtr;

}

#endif // MAP_DESCRIPTION

