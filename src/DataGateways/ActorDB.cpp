#include "ActorDB.h"
#include "utils.h"
#include <fstream>
#include <vector>

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

    while( actorNode != nullptr )
    {
      ActorDescription actorDsc;
      actorDsc.name = actorNode->first_attribute("name")->value();

      std::string charStr = actorNode->first_attribute("character")->value();
      if (charStr.size() > 1 || std::isdigit(charStr[0]))
        actorDsc.character = (unsigned char)std::stol(charStr);
      else
        actorDsc.character = charStr[0];

      string colorStr = actorNode->first_attribute("color")->value();
      actorDsc.color = strToColor(colorStr);

      ActorType id = (ActorType)std::stoi( actorNode->first_attribute("id")->value() );

      actorDsc.blocks = (bool)std::stoi( actorNode->first_attribute("blocks")->value() );
      actorDsc.fovOnly = (bool)std::stoi( actorNode->first_attribute("fovOnly")->value() );
      actorDsc.transparent = (bool)std::stoi( actorNode->first_attribute("transparent")->value() );

      _actors[id] = actorDsc;
      actorNode = actorNode->next_sibling();
    }

    doc.clear();
    success = true;
  }

  return success;
}
