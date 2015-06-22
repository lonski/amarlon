#ifndef MONSTERAI_H
#define MONSTERAI_H

#include <memory>
#include <ai.h>

namespace amarlon {

class MonsterAi;
class Map;
typedef std::shared_ptr<MonsterAi> MonsterAiPtr;
typedef std::shared_ptr<Map> MapPtr;

class MonsterAi : public Ai
{
public:

  class Creator : public Ai::Creator
  {
  public:
    virtual ~Creator() {}
    virtual AiPtr create(AiDescriptionPtr dsc);
  };

  static int TrackingTurns;
  MonsterAi();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs);

  virtual void update();

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
