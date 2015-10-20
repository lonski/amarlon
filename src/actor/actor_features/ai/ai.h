#ifndef AI_H
#define AI_H

#include <memory>
#include <actor_feature.h>
#include <bitset>
#include <ai_type.h>

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
  virtual AiType getAiType() const = 0;

  Ai();
  Ai(DescriptionPtr dsc);
  virtual ~Ai() {}

  static AiPtr create(DescriptionPtr dsc);

  virtual void update() = 0;
  virtual bool performAction(ActorActionPtr action);

  virtual bool isSleeping() const;
  virtual void wakeUp();

  virtual bool isHiding() const;
  virtual void setHiding(bool hiding);

  /**
   * @brief Checks if AI is not sleeping, not paralyzed etc
   *        And can perform actions.
   */
  virtual bool canOperate() const;

  virtual bool isHostileTo(ActorPtr actor) const = 0;
  virtual bool isAllyOf(ActorPtr actor) const = 0;

protected:
  std::bitset<1> _flags;

  void cloneBase(AiPtr ai);
  void updateHidingStatus(ActorActionPtr action);


};

}

#endif // AI_H
