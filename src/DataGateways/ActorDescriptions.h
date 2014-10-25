#ifndef ACTORDESCRIPTIONS_H
#define ACTORDESCRIPTIONS_H

#include <cstring>
#include <string>
#include <vector>
#include <libtcod.hpp>
#include "Actor/ActorType.h"
#include "Actor/ActorFeatures/Ai/AiType.h"
#include "Actor/ActorFeatures/Openable/OpenableType.h"
#include "Actor/Effects/EffectType.h"

namespace amarlon {

class Container;
class Pickable;
class Fighter;
class Ai;
class Openable;

struct EffectDescription
{
  EffectDescription() { memset(this, 0, sizeof *this); }

  EffectType type;
  int lockId;
  int uses;
  int heal;
};

//===
struct ActorDescription
{
  ActorType id;
  std::string name;
  unsigned char character;
  TCODColor color;
  bool blocks;
  bool fovOnly;
  bool transparent;  
};

struct PickableDescription
{
  bool stackable;
  int amount;
  EffectDescription effect;
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
  int lockId;
  bool locked;
};

struct ContainerDescription
{
  struct Content
  {
    ActorType actorType;
    ContainerDescription* container;
    PickableDescription* pickable;
    FighterDescription* fighter;
    AiDescription* ai;
    OpenableDescription* openable;

    Content() { memset(this, 0, sizeof *this); }
  };

  size_t maxSize;
  std::vector<Content> content;
};

//===
}

#endif // ACTORDESCRIPTIONS_H
