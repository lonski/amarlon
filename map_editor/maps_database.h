#ifndef MAPSDATABASE_H
#define MAPSDATABASE_H

#include <string>
#include <persistence/descriptions/map_description.h>

namespace amarlon { namespace map_editor {

class MapsDatabase
{
public:
  MapsDatabase();

  bool load(const std::string& fn);
  bool store(const std::string& fn);
  size_t getMapCount() const;
  std::map<int, MapDescriptionPtr> getMaps() const;
  MapDescriptionPtr getMap(int id) const;

private:
  std::map<int, MapDescriptionPtr> _maps;

};

}}

#endif // MAPSDATABASE_H
