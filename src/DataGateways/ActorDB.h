#ifndef ACTORDB_H
#define ACTORDB_H

#include <map>
#include <string>
#include <vector>
#include <libtcod.hpp>
#include "xml/rapidxml.hpp"
#include "ActorDescriptions.h"

namespace amarlon {

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

}
#endif // ACTORDB_H
