#ifndef AI_H
#define AI_H

#include "AiType.h"

class Actor;
class Map;

class Ai
{
public:
  Ai();
  virtual ~Ai() {}

  void setOwner(Actor* owner);
  virtual void update(Map* map);

  static Ai* create(AiType type);

protected:
  Actor* _owner;

};

#endif // AI_H
