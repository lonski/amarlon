#ifndef MONSTERAI_H
#define MONSTERAI_H

#include "Ai.h"

class MonsterAi : public Ai
{
public:
  static int TrackingTurns;
  MonsterAi();

  virtual void update(Map* map);

  void updatePosition();
private:
  Map* _map;
  int _trackCount;
  int _cX, _cY;

  void retrievePlayerPtr();
  void huntPlayer();

};

#endif // MONSTERAI_H
