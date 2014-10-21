#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <libtcod.hpp>
#include "ActorType.h"
#include "DataGateways/ActorDB.h"
#include "ActorFeatures/Container.h"
#include "ActorFeatures/Pickable.h"
#include "ActorFeatures/Fighter.h"
#include "ActorFeatures/Ai/Ai.h"
#include "ActorFeatures/Openable/Openable.h"

class Map;

class Actor
{
public:
  static ActorDB DB;
  static Actor* Player;

  Actor(ActorType aId, int x = 0, int y = 0);

  void move(int dx, int dy);
  void morph(ActorType newType);
  void changeType(ActorType newType);

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
  Fighter*     afFighter()     const;
  Ai*          afAi()          const;
  Openable*    afOpenable()    const;

  void setAfContainer  (Container*   afContainer);
  void setAfPickable   (Pickable*    afPickable);
  void setAfFighter    (Fighter*     afFighter);
  void setAfAi         (Ai*          afAi);
  void setAfOpenable   (Openable*    afOpenable);

private:
  ActorType _id;
  int _x, _y;

  Container* _afContainer;
  Pickable*  _afPickable;
  Fighter*   _afFighter;
  Ai*        _afAi;
  Openable*  _afOpenable;

};

#endif // ACTOR_H
