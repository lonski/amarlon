#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <memory>
#include "parsers/parser.h"

namespace amarlon {

class Actor;
class Map;
class ActorParser;
typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<ActorParser> ActorParserPtr;

class MapParser : public Parser
{
public:
  MapParser();
  MapParser(rapidxml::xml_node<>* xmlNode);

  MapPtr parse();

private:
  ActorParserPtr _actorParser;
  MapPtr _map;

  void parseActors();
  Actor* parseActor(rapidxml::xml_node<>* actorNode);
  void overWriteActorFeatures(Actor* actor);

};

}

#endif // MAP_PARSER_H
