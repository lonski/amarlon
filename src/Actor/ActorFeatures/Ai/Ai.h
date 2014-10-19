#ifndef AI_H
#define AI_H

#include "../ActorFeature.h"
#include "AiType.h"

class Actor;
class Map;

class Ai : public ActorFeature
{
public:
  Ai();
  virtual ~Ai() {}

  virtual void update(Map* map);

  static Ai* create(AiType type);

};

#endif // AI_H
