#ifndef MAPSDATABASE_H
#define MAPSDATABASE_H

#include <string>
#include <persistence/descriptions/map_description.h>
#include <world/map_id.h>

namespace amarlon { namespace map_editor {

class MapsDatabase
{
public:
  MapsDatabase();

  bool load(const std::string& fn);
  bool store(const std::string& fn);
  size_t getMapCount() const;
  std::map<MapId, MapDescriptionPtr> getMaps() const;
  MapDescriptionPtr getMap(MapId id) const;

private:
  std::map<MapId, MapDescriptionPtr> _maps;

};

}}

#endif // MAPSDATABASE_H
