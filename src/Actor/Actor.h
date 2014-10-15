#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <libtcod.hpp>
#include "ActorType.h"
#include "DataGateways/ActorDB.h"
#include "ActorFeatures/container.h"
#include "ActorFeatures/pickable.h"
#include "ActorFeatures/destrucible.h"
#include "ActorFeatures/attacker.h"
#include "ActorFeatures/ai.h"

class Map;

class Actor
{
public:
  static ActorDB DB;
  static Actor* Player;

  Actor(ActorType aId, int x = 0, int y = 0);

  void move(int dx, int dy);
  void morph(ActorType newType);

  bool isAlive() const;
  bool isFovOnly() const;
  bool isTransparent() const;
  bool blocks() const;

  //read only data
  ActorType getId() const;
  unsigned char getChar() const;
  TCODColor getColor() const;
  std::string getName() const;
  //mutable data
  int getX() const;
  void setX(int getX);
  int getY() const;
  void setY(int getY);

  Container*   afContainer()   const;
  Pickable*    afPickable()    const;
  Destrucible* afDestrucible() const;
  Attacker*    afAttacker()    const;
  Ai*          afAi()          const;

  void setAfContainer  (Container*   afContainer);
  void setAfPickable   (Pickable*    afPickable);
  void setAfDestrucible(Destrucible* afDestrucible);
  void setAfAttacker   (Attacker*    afAttacker);
  void setAfAi         (Ai*          afAi);

private:
  ActorType _id;
  int _x, _y;

  Container* _afContainer;
  Pickable* _afPickable;
  Destrucible* _afDestrucible;
  Attacker* _afAttacker;
  Ai*       _afAi;

};

#endif // ACTOR_H
