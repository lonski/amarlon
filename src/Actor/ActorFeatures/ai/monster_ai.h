#ifndef MONSTERAI_H
#define MONSTERAI_H

#include "ai.h"

namespace amarlon {

class MonsterAi : public Ai
{
public:
  static int TrackingTurns;
  MonsterAi();

  virtual ActorFeature* clone();
  virtual bool isEqual(ActorFeature *rhs);

  virtual void update(Map* map);

  void updatePosition();
private:
  Map* _map;
  int _trackCount;
  int _cX, _cY;

  void retrievePlayerPtr();
  void huntPlayer();

};

}

#endif // MONSTERAI_H
