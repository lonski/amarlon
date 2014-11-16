#ifndef AI_H
#define AI_H

#include "ActorFeature.h"
#include "AiType.h"
#include "DataGateways/ActorDescriptions.h"

namespace amarlon {

class Actor;
class Map;

class Ai : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;

  Ai();
  virtual ~Ai() {}

  virtual ActorFeature::Type getType() { return featureType; }
  virtual void update(Map* map);

  static Ai* create(AiType type);
  static Ai* create(Description* dsc);

};

}

#endif // AI_H
