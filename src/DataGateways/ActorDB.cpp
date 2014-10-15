#include "ActorDB.h"
#include "Utils/Utils.h"
#include <fstream>
#include <vector>
#include "Actor/Actor.h"
#include <algorithm>

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

Container *ActorDB::getContainer(ActorType type)
{
  Container* cont = nullptr;

  if (_containers.count(type))
  {
    ContainerDescription& dsc = _containers[type];
    cont = new Container(dsc.maxSize);

    std::for_each(dsc.content.begin(), dsc.content.end(), [&](ActorType id)
    {
      cont->add(new Actor(id));
    });
  }

  return cont;
}

Pickable *ActorDB::getPickable(ActorType type)
{
  Pickable* pickable = nullptr;

  if (_pickables.count(type))
  {
    //PickableDescription& dsc = _pickables[type];
    pickable = new Pickable;
  }

  return pickable;
}

Destrucible *ActorDB::getDestrucible(ActorType type)
{
  Destrucible* dest = nullptr;

  if (_destrucibles.count(type))
  {
    DestrucibleDescription& dsc = _destrucibles[type];
    dest = new Destrucible(dsc.maxHp);
  }

  return dest;
}

Attacker *ActorDB::getAttacker(ActorType type)
{
  Attacker* att = nullptr;

  if (_attackers.count(type))
  {
    AttackerDescription& dsc = _attackers[type];
    att = new Attacker(dsc.power);
  }

  return att;
}

Ai *ActorDB::getAi(ActorType type)
{
  Ai* ai = nullptr;

  if (_ais.count(type))
  {
    AiDescription& dsc = _ais[type];
    ai = Ai::create(dsc.type);
  }

  return ai;
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
      // ===== ACTOR DESCRIPTION ===== //
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

      // ===== CONTAINER DESCRIPTION ===== //
      xml_node<>* containerNode = actorNode->first_node("Container");
      if ( containerNode )
      {
        ContainerDescription contDsc;
        contDsc.maxSize = std::stol(containerNode->first_attribute("maxSize")->value());

        xml_node<>* contentNode = containerNode->first_node("Content");
        while ( contentNode )
        {
          ActorType aid = (ActorType)std::stol( contentNode->first_attribute("aid")->value() );
          contDsc.content.push_back( aid );

          contentNode = contentNode->next_sibling();
        }

        _containers[id] = contDsc;
      }

      // ===== PICKABLE DESCRIPTION ===== //
      xml_node<>* pickableNode = actorNode->first_node("Pickable");
      if (pickableNode)
      {
        PickableDescription pickDsc;
        _pickables[id] = pickDsc;
      }

      // ===== DESTRUCIBLE DESCRIPTION ===== //
      xml_node<>* destNode = actorNode->first_node("Destrucible");
      if (destNode)
      {
        DestrucibleDescription destDsc;

        destDsc.maxHp = std::stof( destNode->first_attribute("maxHp")->value() );

        _destrucibles[id] = destDsc;
      }

      // ===== DESTRUCIBLE DESCRIPTION ===== //
      xml_node<>* attackerNode = actorNode->first_node("Attacker");
      if (attackerNode)
      {
        AttackerDescription attDsc;

        attDsc.power = std::stof( attackerNode->first_attribute("power")->value() );

        _attackers[id] = attDsc;
      }

      // ===== AI DESCRIPTION ===== //
      xml_node<>* aiNode = actorNode->first_node("Ai");
      if (aiNode)
      {
        AiDescription aiDsc;

        aiDsc.type = (AiType)std::stol( aiNode->first_attribute("type")->value() );

        _ais[id] = aiDsc;
      }

      //~~~~~ NEXT
      actorNode = actorNode->next_sibling();
    }

    doc.clear();
    success = true;
  }

  return success;
}
