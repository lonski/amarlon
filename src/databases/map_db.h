#ifndef MapDB_H
#define MapDB_H

#include <map>
#include <vector>
#include <memory>
#include <xml/rapidxml.hpp>
#include <xml/rapidxml_print.hpp>
#include <persistence/parsers/map_parser.h>

namespace amarlon {

class Map;
class Actor;

typedef std::shared_ptr<Map> MapPtr;

class MapDB
{
public:
  MapDB();
  virtual ~MapDB();

  virtual MapPtr fetch(int id);
  virtual bool load(const std::string& fn);
  virtual bool store(const std::string& fn);

protected:
  MapParser _mapParser;
  std::map<int, MapPtr> _maps;

  void parseMaps(rapidxml::xml_document<> &doc);
  std::shared_ptr< rapidxml::xml_document<> > serializeMaps();

};

typedef std::shared_ptr<MapDB> MapDBPtr;

}

#endif // MapDB_H
