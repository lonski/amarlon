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

class Container;
class Pickable;
class Fighter;
class Ai;
class Openable;

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

struct EffectDescription
{
  EffectDescription() { memset(this, 0, sizeof *this); }

  EffectType type;
  int lockId;
  int uses;
  int heal;
};

struct ContainerDescription
{
  struct AmountedActor
  {
    ActorType type;
    int amount;
  };

  size_t maxSize;
  std::vector<AmountedActor> content;
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

#endif // ACTORDESCRIPTIONS_H
