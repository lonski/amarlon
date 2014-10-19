#ifndef ACTORDESCRIPTIONS_H
#define ACTORDESCRIPTIONS_H

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
  std::string name;
  unsigned char character;
  TCODColor color;
  bool blocks;
  bool fovOnly;
  bool transparent;
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

struct EffectDescription
{
  EffectType type;
  int lockId;
  int uses;
  int heal;
};

#endif // ACTORDESCRIPTIONS_H
