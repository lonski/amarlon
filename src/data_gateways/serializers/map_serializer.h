#ifndef MAP_SERIALIZER_H
#define MAP_SERIALIZER_H

#include <serializer.h>
#include <memory>

namespace amarlon {

class Map;
typedef std::shared_ptr<Map> MapPtr;

class MapSerializer : public Serializer
{
public:
  MapSerializer() {}
  MapSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode)
    : Serializer(document, xmlNode)
  {}

  bool serialize(MapPtr map);

};

}

#endif // MAP_SERIALIZER_H
