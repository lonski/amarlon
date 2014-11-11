#include "ActorDB.h"
#include <utils/utils.h>
#include <fstream>
#include <vector>
#include "Actor/Actor.h"
#include "Actor/Effects/Effect.h"
#include <algorithm>
#include <memory>
#include "Parsers/ActorParser.h"
#include <world/map.h>

namespace amarlon {

using namespace std;
using namespace rapidxml;

ActorDB::ActorDB()
{
}

string ActorDB::getName(ActorType type)
{
  std::string str = "No name";
  if (_actors.count(type))
    str = _actors[type].name;

  return str;
}

unsigned char ActorDB::getChar(ActorType type)
{
  unsigned char ch = 'X';
  if (_actors.count(type))
    ch = _actors[type].character;

  return ch;
}

TCODColor ActorDB::getColor(ActorType type)
{
  return _actors[type].color;
}

bool ActorDB::blocks(ActorType type)
{
  bool a = false;
  if (_actors.count(type))
    a = _actors[type].blocks;

  return a;
}

bool ActorDB::isFovOnly(ActorType type)
{
  bool a = false;
  if (_actors.count(type))
    a = _actors[type].fovOnly;

  return a;
}

bool ActorDB::isTransparent(ActorType type)
{
  bool a = false;
  if (_actors.count(type))
    a = _actors[type].transparent;

  return a;
}

int ActorDB::getTileRenderPriority(ActorType type)
{
  int piority = -1;

  auto found = _actors.find(type);
  if ( found != _actors.end() )
  {
    piority = found->second.tilePriority;
  }

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

Container *ActorDB::getContainer(ActorType type)
{
  return _containers.count(type) ? Container::create( _containers[type] ) : nullptr;
}

Pickable *ActorDB::getPickable(ActorType type)
{
  return _pickables.count(type) ? Pickable::create( _pickables[type] ) : nullptr;
}

Fighter *ActorDB::getFighter(ActorType type)
{
  return _fighters.count(type) ? Fighter::create( _fighters[type] ) : nullptr;
}

Ai *ActorDB::getAi(ActorType type)
{  
  return _ais.count(type) ? Ai::create( _ais[type] ) : nullptr;
}

Openable *ActorDB::getOpenable(ActorType type)
{
  return _openables.count(type) ? Openable::create( _openables[type] ) : nullptr;
}

Wearer *ActorDB::getWearer(ActorType type)
{
  return _wearers.count(type) ? Wearer::create( _wearers[type] ) : nullptr;
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
    xml_node<>* actorNode = root->first_node("Actor");

    ActorParser actorParser;
    while( actorNode != nullptr )
    {
      actorParser.setSource( actorNode );

      unique_ptr<ActorDescription> actorDsc( actorParser.parseActorDsc() );
      if ( actorDsc )
      {
        ActorType id = actorDsc->id;
        _actors[id] = *actorDsc;

        unique_ptr<ContainerDescription> contDsc( actorParser.parseContainerDsc() );
        if ( contDsc ) _containers[id] = *contDsc;

        unique_ptr<PickableDescription> pickDsc( actorParser.parsePickableDsc() );
        if ( pickDsc ) _pickables[id] = *pickDsc;

        unique_ptr<FighterDescription> fDsc( actorParser.parseFighterDsc() );
        if ( fDsc ) _fighters[id] = *fDsc;

        unique_ptr<AiDescription> aiDsc( actorParser.parseAiDsc() );
        if ( aiDsc ) _ais[id] = *aiDsc;

        unique_ptr<OpenableDescription> opDsc( actorParser.parseOpenableDsc() );
        if ( opDsc ) _openables[id] = *opDsc;

        unique_ptr<WearerDescription> wrDsc( actorParser.parseWearerDsc() );
        if ( wrDsc ) _wearers[id] = *wrDsc;
      }

      //~~~~~ NEXT
      actorNode = actorNode->next_sibling();
    }

    doc.clear();
    success = true;
  }

  return success;
}

}
