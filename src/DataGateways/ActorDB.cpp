#include "ActorDB.h"
#include <fstream>
#include <vector>
#include <algorithm>
#include <utils/utils.h>
#include <Actor/Actor.h>
#include <Actor/Effects/Effect.h>
#include <Parsers/ActorParser.h>
#include <world/map.h>

namespace amarlon {

using namespace std;
using namespace rapidxml;

ActorDB::ActorDB()
{
}

string ActorDB::getName(ActorType type)
{
  return getParam<std::string>(type, &ActorDescription::name, "No name");
}

unsigned char ActorDB::getChar(ActorType type)
{
  return getParam<unsigned char>(type, &ActorDescription::character, 'X');
}

TCODColor ActorDB::getColor(ActorType type)
{
  return getParam<TCODColor>(type, &ActorDescription::color, TCODColor::white);
}

bool ActorDB::blocks(ActorType type)
{
  return getParam<bool>(type, &ActorDescription::blocks, false);
}

bool ActorDB::isFovOnly(ActorType type)
{
  return getParam<bool>(type, &ActorDescription::fovOnly, false);
}

bool ActorDB::isTransparent(ActorType type)
{
  return getParam<bool>(type, &ActorDescription::transparent, false);
}

int ActorDB::getTileRenderPriority(ActorType type)
{
  int piority = getParam<int>(type, &ActorDescription::tilePriority, -1);

  //not set in xml, set default prority for particural actor type
  if ( piority == -1 )
  {
    switch( type )
    {
      case ActorType::DoorOpen:
      case ActorType::DoorClosed:
      {
        piority = Tile::defaultItemRenderPriority + 1;
      }
      break;
      default:;
    }
  }

  return piority;
}

bool ActorDB::loadActors(std::string fn)
{
  bool success = false;
  ifstream ifs(fn);

  if (ifs.is_open())
  {
    vector<char> buffer;
    buffer.assign(istreambuf_iterator<char>(ifs), istreambuf_iterator<char>());
    buffer.push_back('\0');

    xml_document<> doc;
    doc.parse<0>(&buffer[0]);

    xml_node<>* root = doc.first_node("Actors");
    if (root != nullptr)
    {
      xml_node<>* actorNode = root->first_node("Actor");

      ActorParser actorParser;
      while( actorNode != nullptr )
      {
        actorParser.setSource( actorNode );

        ActorDescription* actorDsc = actorParser.parseActorDsc();
        if ( actorDsc != nullptr )
        {
          ActorType actorId = actorDsc->id;
          DescriptionMap actorDescriptions;

          actorDescriptions[typeid(Actor).name()] = DescriptionPtr(actorDsc);

          DescriptionPtr contDsc( actorParser.parseContainerDsc() );
          if ( contDsc ) actorDescriptions[typeid(Container).name()] = contDsc;

          DescriptionPtr pickDsc( actorParser.parsePickableDsc() );
          if ( pickDsc ) actorDescriptions[typeid(Pickable).name()] = pickDsc;

          DescriptionPtr fDsc( actorParser.parseFighterDsc() );
          if ( fDsc ) actorDescriptions[typeid(Fighter).name()] = fDsc;

          DescriptionPtr aiDsc( actorParser.parseAiDsc() );
          if ( aiDsc ) actorDescriptions[typeid(Ai).name()] = aiDsc;

          DescriptionPtr opDsc( actorParser.parseOpenableDsc() );
          if ( opDsc ) actorDescriptions[typeid(Openable).name()] = opDsc;

          DescriptionPtr wrDsc( actorParser.parseWearerDsc() );
          if ( wrDsc ) actorDescriptions[typeid(Wearer).name()] = wrDsc;

          _descriptions[actorId] = actorDescriptions;
        }

        //~~~~~ NEXT
        actorNode = actorNode->next_sibling();
      }
    }
    doc.clear();
    success = true;
  }

  return success;
}

}
