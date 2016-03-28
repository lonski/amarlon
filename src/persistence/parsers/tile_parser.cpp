#include "tile_parser.h"
#include <utils/xml_utils.h>
#include <utils/utils.h>

namespace amarlon {

TileParser::TileParser(rapidxml::xml_node<> *xmlNode)
  : Parser(xmlNode)
{
}

TileDescription* TileParser::parseTileDsc()
{
  TileDescription* tileDsc = nullptr;

  if ( _xml != nullptr)
  {
    tileDsc = new TileDescription;

    tileDsc->type =  getAttribute<int>(_xml, "id");
    tileDsc->character = getAttribute<std::string>(_xml, "character").front();
    tileDsc->color = getAttribute<std::string>(_xml, "color");
    tileDsc->walkable = getAttribute<bool>(_xml, "walkable");
    tileDsc->transparent = getAttribute<bool>(_xml, "transparent");
  }

  return tileDsc;
}

}

