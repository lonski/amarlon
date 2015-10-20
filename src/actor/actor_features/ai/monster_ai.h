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
  static int TrackingTurns;
  const static ActorFeature::Type featureType;
  virtual AiType getAiType() const;

  MonsterAi(AiDescriptionPtr dsc);
  MonsterAi();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  virtual void update();
  virtual bool isHunting() const;

  virtual bool isHostileTo(ActorPtr actor) const;
  virtual bool isAllyOf(ActorPtr actor) const;

private:
  MapPtr _map;
  int _trackCount;
  int _cX, _cY;

  void retrievePlayerPtr();
  void huntPlayer();
  void updatePosition();

};

}

#endif // MONSTERAI_H
