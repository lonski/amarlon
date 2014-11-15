#ifndef TILE_PARSER_H
#define TILE_PARSER_H

#include <Parsers/parser.h>
#include <descriptions/tile_description.h>

namespace amarlon {

class TileParser : public Parser
{
public:
  TileParser() {}
  TileParser(rapidxml::xml_node<>* xmlNode);

  TileDescription* parseTileDsc();

};

}

#endif // TILE_PARSER_H
