#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <libtcod.hpp>
#include "ActorType.h"
#include "DataGateways/ActorDB.h"

class Map;

class Actor
{
public:
  static ActorDB DB;

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

private:
  ActorType _id;
  int _x, _y;

};

#endif // ACTOR_H
