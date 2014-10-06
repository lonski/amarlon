#ifndef ACTOR_H
#define ACTOR_H

#include <string>
#include <libtcod.hpp>

class Map;

class Actor
{
public:
  Actor(const std::string& name,
        char ch,
        int getX = 0,
        int getY = 0,
        TCODColor getColor = TCODColor::white);

  void move(int dx, int dy);

  //read only data
  char getChar() const;  
  TCODColor getColor() const;
  std::string getName() const;
  //mutable data
  int getX() const;
  void setX(int getX);
  int getY() const;
  void setY(int getY);

private:
  int _x, _y;
  char _ch;
  std::string _name;
  TCODColor _color;

};

#endif // ACTOR_H
