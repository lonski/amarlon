#include "map_parser.h"
#include <string>
#include <xml_utils.h>
#include <map.h>
#include <actor_parser.h>
#include <actor.h>
#include <teleport_action.h>
#include <fstream>

namespace amarlon {

MapParser::MapParser()
  : _actorParser( new ActorParser)
{
}

MapParser::MapParser(rapidxml::xml_node<> *xmlNode)
  : Parser(xmlNode)
  , _actorParser( new ActorParser )
{
}

MapDescriptionPtr MapParser::parseDescription()
{
  MapDescriptionPtr mDsc;
  if ( _xml )
  {
    mDsc.reset( new MapDescription );

    mDsc->width = getAttribute<int>(_xml, "width");
    mDsc->height = getAttribute<int>(_xml, "height");
    mDsc->id = getAttribute<int>(_xml, "id");
    mDsc->name = getAttribute<std::string>(_xml, "name");
    mDsc->binaryTiles = getNodeValue<std::string>( _xml->first_node("Tiles") );

    //Parse Actors
    rapidxml::xml_node<>* actorsRoot = _xml->first_node("Actors");
    if (actorsRoot != nullptr)
    {
      rapidxml::xml_node<>* actorNode = actorsRoot->first_node("Actor");
      while ( actorNode != nullptr )
      {
        _actorParser->setSource( actorNode );
        mDsc->actors.push_back( _actorParser->parseDescription() );
        actorNode = actorNode->next_sibling();
      }
    }

    //Parse Actions
    rapidxml::xml_node<>* onExitNode = _xml->first_node("OnExit");
    if ( onExitNode != nullptr )
    {
      rapidxml::xml_node<>* directionNode = onExitNode->first_node("Direction");
      while ( directionNode != nullptr )
      {
        ActorActionDescriptionPtr aDsc(new ActorActionDescription);
        int direction = getAttribute<int>(directionNode, "id");

        rapidxml::xml_node<>* teleportNode = directionNode->first_node("Teleport");
        if ( teleportNode != nullptr )
        {
          aDsc->teleport_MapId = getAttribute<int>(teleportNode, "mapId");
          aDsc->teleport_x = getAttribute<int>(teleportNode, "x");
          aDsc->teleport_y = getAttribute<int>(teleportNode, "y");
          mDsc->actions[ direction ] = aDsc;
        }

        directionNode = directionNode->next_sibling();
      }
    }

  }
  return mDsc;
}

}

