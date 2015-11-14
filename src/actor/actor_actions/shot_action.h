#ifndef SHOT_ACTION_H
#define SHOT_ACTION_H

#include <memory>
#include <actor_action.h>

namespace amarlon {

class Pickable;
typedef std::shared_ptr<Pickable> PickablePtr;

class ShotAction : public ActorAction
{
public:
    ShotAction(ActorPtr target);
    virtual ~ShotAction();

    virtual bool perform(ActorPtr performer);
    virtual ActorActionUPtr clone();

private:
    ActorPtr _target;
    ActorPtr _performer;

    PickablePtr getWeapon();
    PickablePtr getAmunition();
    bool isReadyToShot();
    bool isTargetCorrect();
    int calculateAttackBonusModifier();

};

typedef std::shared_ptr<ShotAction> ShotActionPtr;
typedef std::unique_ptr<ShotAction> ShotActionUPtr;

}
#endif // SHOT_ACTION_H
