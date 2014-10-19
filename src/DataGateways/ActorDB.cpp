#include "ActorDB.h"
#include "Utils/Utils.h"
#include <fstream>
#include <vector>
#include "Actor/Actor.h"
#include "Actor/Effects/Effect.h"
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

    std::for_each(dsc.content.begin(), dsc.content.end(), [&](ContainerDescription::AmountedActor aa)
    {
      Actor* nActor = new Actor(aa.type);
      nActor->afPickable()->setAmount(aa.amount);
      cont->add(nActor);
    });
  }

  return cont;
}

Pickable *ActorDB::getPickable(ActorType type)
{
  Pickable* pickable = nullptr;

  if (_pickables.count(type))
  {
    PickableDescription& pDsc = _pickables[type];
    pickable = new Pickable(pDsc.stackable, pDsc.amount);

    if (_effects.count(type))
    {
      EffectDescription& eDsc = _effects[type];
      Effect* effect = Effect::create(eDsc.type);
      effect->load(eDsc);

      pickable->setEffect(effect);
    }
  }

  return pickable;
}

Fighter *ActorDB::getFighter(ActorType type)
{
  Fighter* f = nullptr;

  if (_fighters.count(type))
  {
    FighterDescription& dsc = _fighters[type];
    f = new Fighter(dsc.power, dsc.maxHp);
  }

  return f;
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

Openable *ActorDB::getOpenable(ActorType type)
{
  Openable* op = nullptr;

  if (_openables.count(type))
  {
    OpenableDescription& dsc = _openables[type];
    op = Openable::create(dsc.type);

    op->setLockId(dsc.lockId);
    op->_locked = dsc.locked;
  }

  return op;
}

template<typename T>
T getAttribute(xml_node<>* node, std::string attribute)
{
  T result(0);
  xml_attribute<>* nodeAtr = node->first_attribute(attribute.c_str());

  if ( nodeAtr )
  {
    std::string value = nodeAtr->value();

    std::stringstream ss;
    ss << value;
    ss >> result;
  }

  return result;
}

template<>
std::string getAttribute<std::string>(xml_node<>* node, std::string attribute)
{
  xml_attribute<>* nodeAtr = node->first_attribute(attribute.c_str());
  std::string value;

  if ( nodeAtr )
  {
    value = nodeAtr->value();
  }

  return value;
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
      actorDsc.name = getAttribute<std::string>(actorNode, "name");

      std::string charStr = getAttribute<std::string>(actorNode, "character");
      if (charStr.size() > 1 || std::isdigit(charStr[0]))
        actorDsc.character = (unsigned char)std::stol(charStr);
      else
        actorDsc.character = charStr[0];

      string colorStr = getAttribute<std::string>(actorNode, "color");
      actorDsc.color = strToColor(colorStr);

      ActorType id = (ActorType)getAttribute<int>(actorNode, "id");

      actorDsc.blocks = getAttribute<bool>(actorNode, "blocks");
      actorDsc.fovOnly = getAttribute<bool>(actorNode, "fovOnly");
      actorDsc.transparent = getAttribute<bool>(actorNode, "transparent");

      _actors[id] = actorDsc;

      // ===== CONTAINER DESCRIPTION ===== //
      xml_node<>* containerNode = actorNode->first_node("Container");
      if ( containerNode )
      {
        ContainerDescription contDsc;

        contDsc.maxSize = getAttribute<int>(containerNode, "maxSize");

        xml_node<>* contentNode = containerNode->first_node("Content");
        while ( contentNode )
        {          
          ContainerDescription::AmountedActor cActor;
          cActor.type = (ActorType)getAttribute<int>(contentNode, "aid");
          cActor.amount = getAttribute<int>(contentNode, "amount");
          if (cActor.amount == 0) cActor.amount = 1;

          contDsc.content.push_back( cActor );

          contentNode = contentNode->next_sibling();
        }

        _containers[id] = contDsc;
      }

      // ===== PICKABLE DESCRIPTION ===== //
      xml_node<>* pickableNode = actorNode->first_node("Pickable");
      if (pickableNode)
      {
        PickableDescription pickDsc;

        pickDsc.stackable = getAttribute<bool>(pickableNode, "stackable");
        pickDsc.amount = getAttribute<int>(pickableNode, "amount");
        if ( pickDsc.amount == 0) pickDsc.amount = 1;

        _pickables[id] = pickDsc;

        // == effects == //
        xml_node<>* effectNode = pickableNode->first_node("Effect");
        if ( effectNode )
        {
          EffectDescription effDsc;
          effDsc.type = (EffectType)getAttribute<int>(effectNode, "type");
          effDsc.lockId = getAttribute<int>(effectNode, "lockId");
          effDsc.uses = getAttribute<int>(effectNode, "uses");
          effDsc.heal = getAttribute<int>(effectNode, "heal");

          _effects[id] = effDsc;
        }
      }

      // ===== DESTRUCIBLE DESCRIPTION ===== //
      xml_node<>* fighterNode = actorNode->first_node("Fighter");
      if (fighterNode)
      {
        FighterDescription fDsc;

        fDsc.power = getAttribute<float>(fighterNode, "power");
        fDsc.maxHp = getAttribute<float>(fighterNode, "maxHp");

        _fighters[id] = fDsc;
      }

      // ===== AI DESCRIPTION ===== //
      xml_node<>* aiNode = actorNode->first_node("Ai");
      if (aiNode)
      {
        AiDescription aiDsc;

        aiDsc.type = (AiType)getAttribute<int>(aiNode, "type");

        _ais[id] = aiDsc;
      }

      // ===== OPENABLE DESCRIPTION ===== //
      xml_node<>* openableNode = actorNode->first_node("Openable");
      if (openableNode)
      {
        OpenableDescription opDsc;

        opDsc.type = (OpenableType)getAttribute<int>(openableNode, "type");
        opDsc.lockId = getAttribute<int>(openableNode, "lockId");
        opDsc.locked = getAttribute<bool>(openableNode, "locked");
        _openables[id] = opDsc;
      }

      //~~~~~ NEXT
      actorNode = actorNode->next_sibling();
    }

    doc.clear();
    success = true;
  }

  return success;
}
