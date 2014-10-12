#ifndef ACTORDB_H
#define ACTORDB_H

#include <map>
#include <string>
#include <vector>
#include <libtcod.hpp>
#include "xml/rapidxml.hpp"
#include "Actor/ActorType.h"
#include "Actor/ActorFeatures/AiType.h"

class Container;
class Pickable;
class Destrucible;
class Attacker;
class Ai;

struct ActorDescription
{
  std::string name;
  unsigned char character;
  TCODColor color;
  bool blocks;
  bool fovOnly;
  bool transparent;
};

struct ContainerDescription
{
  size_t maxSize;
  std::vector<ActorType> content;
};

struct PickableDescription
{

};

struct DestrucibleDescription
{
  float maxHp;
};

struct AttackerDescription
{
  float power;
};

struct AiDescription
{
  AiType type;
};

class ActorDB
{
public:
  ActorDB();

  std::string getName(ActorType type);
  unsigned char getChar(ActorType type);
  TCODColor getColor(ActorType type);
  bool blocks(ActorType type);
  bool isFovOnly(ActorType type);
  bool isTransparent(ActorType type);

  //ActorFeatures
  Container* getContainer(ActorType type);
  Pickable* getPickable(ActorType type);
  Destrucible* getDestrucible(ActorType type);
  Attacker* getAttacker(ActorType type);
  Ai* getAi(ActorType type);

  bool loadActors(std::string fn);

private:
  std::map<ActorType, ActorDescription> _actors;
  std::map<ActorType, ContainerDescription> _containers;
  std::map<ActorType, PickableDescription> _pickables;
  std::map<ActorType, DestrucibleDescription> _destrucibles;
  std::map<ActorType, AttackerDescription> _attackers;
  std::map<ActorType, AiDescription> _ais;

};

#endif // ACTORDB_H
