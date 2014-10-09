#ifndef ACTORDB_H
#define ACTORDB_H

#include <map>
#include <string>
#include <libtcod.hpp>
#include "xml/rapidxml.hpp"
#include "Actor/ActorType.h"

struct ActorDescription
{
  std::string name;
  unsigned char character;
  TCODColor color;
  bool blocks;
  bool fovOnly;
  bool transparent;
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

  bool loadActors(std::string fn);

private:
  std::map<ActorType, ActorDescription> _actors;

};

#endif // ACTORDB_H
