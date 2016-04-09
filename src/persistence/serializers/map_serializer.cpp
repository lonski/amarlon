#include "map_serializer.h"
#include <string>
#include <utils.h>
#include <xml_utils.h>
#include <actor_descriptions.h>
#include <map_description.h>

using namespace rapidxml;
using namespace std;

namespace amarlon {

MapSerializer::MapSerializer()
  : MapSerializer(nullptr, nullptr)
{
}

MapSerializer::MapSerializer(rapidxml::xml_document<> *document, rapidxml::xml_node<> *xmlNode)
  : Serializer(document, xmlNode)
{
}

MapSerializer::~MapSerializer()
{
}

bool MapSerializer::serialize(DescriptionPtr dsc)
{
  MapDescriptionPtr mDsc = std::dynamic_pointer_cast<MapDescription>(dsc);
  if ( mDsc )
  {
    rapidxml::xml_node<>* _mapNode = _document->allocate_node(node_element, "Map");
    _xml->append_node(_mapNode);

    addAttribute(_mapNode, "height", mDsc->height );
    addAttribute(_mapNode,  "width", mDsc->width );
    addAttribute(_mapNode,  "name", mDsc->name );
    addAttributeEnum(_mapNode, "id", mDsc->id );
    _mapNode->append_node( createNode(_document, "Tiles", mDsc->binaryTiles) );

    xml_node<>* actorsNode = createNode(_document, "Actors", "");
    _mapNode->append_node( actorsNode );

    _actorSerializer.setDestination(_document, actorsNode);
    for ( auto a : mDsc->actors )
    {
      _actorSerializer.serialize(a);
    }

    xml_node<>* exitActionsNode = createNode(_document, "OnExit", "");
    _mapNode->append_node( exitActionsNode );

    for ( auto& kv : mDsc->actions )
    {
      xml_node<>* directionNode = createNode(_document, "Direction", "");

      exitActionsNode->append_node(directionNode);
      addAttributeEnum( directionNode, "id", kv.first );

      _actionSerializer.setDestination(_document, directionNode);
      _actionSerializer.serialize( kv.second );
    }

    return true;
  }
  return false;
}

}

