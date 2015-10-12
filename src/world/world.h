#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <map>
#include <map_id.h>
#include <map_gateway.h>

namespace amarlon {

class Map;
class Actor;
typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<Actor> ActorPtr;

class World : public MapGateway
{
public:
  World(const std::string& mapsFile);
  virtual ~World();

  virtual MapPtr fetch(MapId id);
  virtual MapPtr getCurrentMap();
  virtual void changeMap(MapId id);
  virtual const ActorPtr getPlayer();
  virtual void setPlayer(ActorPtr player);

  virtual bool store(const std::string& fn);
  bool load(const std::string& fn);

private:  
  MapId _currentMap;
  ActorPtr _player;
  MapGatewayPtr _mapGateway;

  void parsePlayer(rapidxml::xml_document<>& doc);
  void parseCurrentMap(rapidxml::xml_document<>& doc);

};

}

#endif // WORLD_H
