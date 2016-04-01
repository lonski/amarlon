#ifndef MapDB_H
#define MapDB_H

#include <map>
#include <vector>
#include <memory>
#include <xml/rapidxml.hpp>
#include <xml/rapidxml_print.hpp>
#include <world/map_id.h>

namespace amarlon {

class Map;
class Actor;

typedef std::shared_ptr<Map> MapPtr;

class MapDB
{
public:
  MapDB();
  virtual ~MapDB();

  virtual MapPtr fetch(MapId id);
  virtual bool load(const std::string& fn);
  virtual bool store(const std::string& fn);

protected:
  std::map<MapId, MapPtr> _maps;

};

typedef std::shared_ptr<MapDB> MapDBPtr;

}

#endif // MapDB_H
