#ifndef AI_H
#define AI_H

#include <memory>
#include <actor_feature.h>

namespace amarlon {

class Ai;
class ActorAction;
struct AiDescription;
typedef std::shared_ptr<Ai> AiPtr;
typedef std::shared_ptr<ActorAction> ActorActionPtr;
typedef std::shared_ptr<AiDescription> AiDescriptionPtr;

class Ai : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;
  virtual ActorFeature::Type getType() { return featureType; }

  Ai();
  Ai(DescriptionPtr dsc);
  virtual ~Ai() {}

  static AiPtr create(DescriptionPtr dsc);

  virtual void update() = 0;
  virtual bool performAction(ActorActionPtr action);

  virtual bool isSleeping() const;
  virtual void wakeUp();

  /**
   * @brief Checks if AI is not sleeping, not paralyzed etc
   *        And can perform actions.
   */
  virtual bool canOperate() const;

protected:
  void cloneBase(AiPtr ai);


};

}

#endif // AI_H
