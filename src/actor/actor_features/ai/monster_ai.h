#ifndef MONSTERAI_H
#define MONSTERAI_H

#include <memory>
#include "ai.h"

namespace amarlon {

class MonsterAi;
typedef std::shared_ptr<MonsterAi> MonsterAiPtr;

class MonsterAi : public Ai
{
public:
  static int TrackingTurns;
  MonsterAi();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs);

  virtual void update(MapPtr map);

  void updatePosition();
private:
  MapPtr _map;
  int _trackCount;
  int _cX, _cY;

  void retrievePlayerPtr();
  void huntPlayer();

};

}

#endif // MONSTERAI_H
