#ifndef MAP_DESCRIPTION
#define MAP_DESCRIPTION

#include <vector>
#include <memory>
#include <description.h>

namespace amarlon {

struct ActorDescription;

struct MapActionDescription
{
  int direction;
  int teleport_MapId;
  int teleport_x;
  int teleport_y;
};

typedef std::shared_ptr<ActorDescription> ActorDescriptionPtr;
typedef std::shared_ptr<MapActionDescription> MapActionDescriptionPtr;

struct MapDescription : Description
{
  int id;
  int width;
  int height;
  std::string binaryTiles;
  std::vector<ActorDescriptionPtr> actors;
  std::vector<MapActionDescriptionPtr> actions;
};

typedef std::shared_ptr<MapDescription> MapDescriptionPtr;

}

#endif // MAP_DESCRIPTION

