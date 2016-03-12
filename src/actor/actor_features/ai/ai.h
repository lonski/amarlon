#ifndef AI_H
#define AI_H

#include <memory>
#include <actor_feature.h>
#include <bitset>
#include <ai_type.h>
#include <fsm_state_type.h>
#include <target.h>
#include <actor_action_result.h>
#include <actor.pb.h>

namespace amarlon {

class Ai;
class ActorAction;
struct AiDescription;
class FSM;
typedef std::shared_ptr<Ai> AiPtr;
typedef std::shared_ptr<FSM> FSMPtr;
typedef std::shared_ptr<ActorAction> ActorActionPtr;
typedef std::shared_ptr<AiDescription> AiDescriptionPtr;
typedef std::vector<ActorPtr> ActorVector;

class Ai : public ActorFeature
{
public:
  const static ActorFeature::Type featureType;
  virtual ActorFeature::Type getType() { return featureType; }
  virtual AiType getAiType() const;

  Ai(DescriptionPtr dsc = nullptr);
  virtual void upgrade(DescriptionPtr dsc);
  virtual DescriptionPtr toDescriptionStruct(ActorFeaturePtr cmp = nullptr);
  virtual ~Ai() {}

  static AiPtr create(DescriptionPtr dsc);
  virtual bool isEqual(ActorFeaturePtr rhs) const;
  virtual ActorFeaturePtr clone();
  bool operator==(const Ai& rhs) const;
  Ai& operator=(const Ai& rhs);

  virtual int update();
  virtual ActorActionResult performAction(ActorActionPtr action);

  virtual bool isSleeping() const;
  virtual void wakeUp();

  virtual bool isHiding() const;
  virtual void setHiding(bool hiding);

  virtual bool isSneaking() const;
  virtual void setSneaking(bool sneaking);

  virtual bool changeState(FSMStateType type);
  virtual FSMStateType getCurrentState() const;

  /**
   * @brief Checks if AI is not sleeping, not paralyzed etc
   *        And can perform actions.
   */
  virtual bool canOperate() const;

  /**
   * @brief Associated script path
   */
  std::string getScript() const;

  /**
   * @brief Current target of actions (in most cases choosen enemy)
   */
  void setTarget(Target target);
  void setTarget(ActorPtr actor);
  Target getTarget() const;
  bool hasTarget() const;
  void clearTarget();

  ActorVector getEnemiesInFov() const;

  virtual int getTrackingTurns() const;
  virtual void setTrackingTurns(int turns);

  bool isHunting() const;

  virtual std::string debug(const std::string &linebreak);

protected:
  AiData _data;

  FSMPtr _fsm;
  Target _currentTarget;
  int _trackCount;

  void executeScript();
  void updateHidingStatus(ActorActionPtr action);
  void updateSneakingStatus(ActorActionPtr action);

};

}

#endif // AI_H
