#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <map>
#include <map_db.h>

namespace amarlon {

class Map;
class Actor;
typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<Actor> ActorPtr;

class World : public MapDB
{
public:
  World();
  virtual ~World();

  virtual MapPtr fetch(int id);
  virtual MapPtr getCurrentMap();
  virtual void changeMap(int id);
  virtual const ActorPtr getPlayer();
  virtual void setPlayer(ActorPtr player);

  virtual bool store(const std::string& fn);
  virtual bool load(const std::string& fn);
  virtual bool loadPlugin(const std::string& fn);

private:  
  int _currentMap;
  ActorPtr _player;
  MapDBPtr _mapDB;

  void parsePlayer(rapidxml::xml_document<>& doc);
  void parseCurrentMap(rapidxml::xml_document<>& doc);

};

}

#endif // WORLD_H
