#include "world.h"
#include <map.h>
#include <vector>
#include <fstream>
#include <actor_serializer.h>
#include <actor_parser.h>
#include <actor.h>
#include <actor_descriptions.h>
#include <utils/xml_utils.h>

using namespace rapidxml;

namespace amarlon {

World::World()
  : _currentMap(0)
  , _mapDB( new MapDB )
{
}

World::~World()
{
}

MapPtr World::getCurrentMap()
{
  return fetch(_currentMap);
}

MapPtr World::fetch(int id)
{
  MapPtr map;

  auto mIter = _maps.find(id);
  if ( mIter != _maps.end() )
  {
    map = mIter->second;
  }
  else
  {
    map = _mapDB->fetch(id);
    _maps.insert( std::make_pair(id, map) );
  }

  return map;
}

void World::changeMap(int id)
{
  _currentMap = id;
}

const ActorPtr World::getPlayer()
{
  return _player;
}

void World::setPlayer(ActorPtr player)
{
  if ( player )
  {
    if ( _player ) getCurrentMap()->removeActor( _player );
    _player = player;
    getCurrentMap()->addActor( _player );
  }
  else throw std::logic_error("Cant set null player!");
}

bool World::store(const std::string &fn)
{
  std::ofstream ofs(fn, std::ios_base::app | std::ios_base::out);
  if ( ofs.is_open() )
  {
    getCurrentMap()->removeActor( getPlayer() );

    std::shared_ptr<xml_document<> > doc = serializeMaps();

    //create node for save info
    xml_node<>* saveNode = doc->allocate_node(node_element, "Save");
    doc->append_node(saveNode);

    //save Player
    ActorSerializer actorSerializer(doc.get(), saveNode);
    actorSerializer.serialize(_player->toDescriptionStruct());

    //save current Map
    xml_node<>* cMapNode = doc->allocate_node(node_element, "CurrentMap");
    saveNode->append_node(cMapNode);
    addAttributeEnum( cMapNode, "id", _currentMap );

    ofs << *doc;

    //put back player
    getCurrentMap()->addActor( getPlayer() );

    return true;
  }
  return false;
}

bool World::load(const std::string& fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buf.push_back('\0');

    xml_document<> doc;
    doc.parse<0>(&buf[0]);

    parseMaps(doc);
    parseCurrentMap(doc);
    parsePlayer(doc);

    return true;
  }
  return false;
}

bool World::loadPlugin(const std::string &fn)
{
  std::ifstream ifs(fn);

  if (ifs.is_open())
  {
    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
    buf.push_back('\0');

    xml_document<> doc;
    doc.parse<0>(&buf[0]);

    parseMaps(doc);

    return true;
  }
  return false;
}

void World::parsePlayer(rapidxml::xml_document<> &doc)
{
  xml_node<>* save = doc.first_node("Save");
  xml_node<>* playerNode = save ? save->first_node("Actor") : nullptr;

  if(playerNode != nullptr)
  {
    ActorParser parser(playerNode);
    _player = Actor::create( parser.parseDescription() );
    getCurrentMap()->addActor( _player );
  }
}

void World::parseCurrentMap(rapidxml::xml_document<> &doc)
{
  xml_node<>* save = doc.first_node("Save");
  xml_node<>* cMapNode = save ? save->first_node("CurrentMap") : nullptr;

  if(cMapNode != nullptr)
  {
    _currentMap = getAttribute<int>(cMapNode, "id");
  }
}

}

