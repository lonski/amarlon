#ifndef ACTORDB_H
#define ACTORDB_H

#include <map>
#include <string>
#include <vector>
#include <libtcod.hpp>
#include "xml/rapidxml.hpp"
#include "Actor/ActorType.h"
#include "Actor/ActorFeatures/Ai/AiType.h"
#include "Actor/ActorFeatures/Openable/OpenableType.h"

class Container;
class Pickable;
class Fighter;
class Ai;
class Openable;

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
  bool stackable;
  int amount;
};

struct FighterDescription
{
  float maxHp;
  float power;
};

struct AiDescription
{
  AiType type;
};

struct OpenableDescription
{
  OpenableType type;
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
  Fighter* getFighter(ActorType type);
  Ai* getAi(ActorType type);
  Openable* getOpenable(ActorType type);

  bool loadActors(std::string fn);

private:
  std::map<ActorType, ActorDescription> _actors;
  std::map<ActorType, ContainerDescription> _containers;
  std::map<ActorType, PickableDescription> _pickables;
  std::map<ActorType, FighterDescription> _fighters;
  std::map<ActorType, AiDescription> _ais;
  std::map<ActorType, OpenableDescription> _openables;

};

#endif // ACTORDB_H
