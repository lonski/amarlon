#ifndef MAP_SERIALIZER_H
#define MAP_SERIALIZER_H

#include <serializer.h>
#include <action_serializer.h>
#include <actor_serializer.h>
#include <memory>

namespace amarlon {

class Map;
typedef std::shared_ptr<Map> MapPtr;

class MapSerializer : public Serializer
{
public:
  MapSerializer();
  MapSerializer(rapidxml::xml_document<>* document, rapidxml::xml_node<>* xmlNode);
  virtual ~MapSerializer();

  virtual bool serialize(MapPtr map);

private:
  ActionSerializer _actionSerializer;
  ActorSerializer _actorSerializer;
  rapidxml::xml_node<>* _mapNode;
  MapPtr _map;

  void serializeExitActions();

};

}

#endif // MAP_SERIALIZER_H
