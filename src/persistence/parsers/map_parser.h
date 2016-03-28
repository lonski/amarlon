#ifndef MAP_PARSER_H
#define MAP_PARSER_H

#include <memory>
#include <persistence/parsers/parser.h>
#include <map_description.h>

namespace amarlon {

class Actor;
class Map;
class ActorParser;
typedef std::shared_ptr<Map> MapPtr;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<ActorParser> ActorParserPtr;

class MapParser : public Parser
{
public:
  MapParser();
  MapParser(rapidxml::xml_node<>* xmlNode);

  MapDescriptionPtr parseDescription();

private:
  ActorParserPtr _actorParser;

};

}

#endif // MAP_PARSER_H
