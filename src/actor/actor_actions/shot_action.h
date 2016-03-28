#ifndef SHOT_ACTION_H
#define SHOT_ACTION_H

#include <memory>
#include <actor_action.h>
#include <point.h>

namespace amarlon {

class Pickable;
class DirectPath;
typedef std::shared_ptr<Pickable> PickablePtr;
typedef std::shared_ptr<DirectPath> DirectPathPtr;

class ShotAction : public ActorAction
{
public:
    ShotAction(ActorPtr target);
    virtual ~ShotAction();

    virtual ActorActionResult perform(ActorPtr performer);
    virtual ActorActionUPtr clone();

private:
    ActorPtr _target;
    ActorPtr _performer;

    PickablePtr getWeapon();
    PickablePtr getAmunition();
    bool isReadyToShot();
    bool isTargetCorrect();
    int calculateAttackBonusModifier();
    DirectPathPtr calculatePath();
    ActorPtr getTarget(const Point& p);
    void dropMissile(ActorPtr missile, const Point& p, int chance);
    ActorPtr pickOneMissile();
    bool rangeAttack(ActorPtr actor);
    void renderMissile(const Point& prev, const Point& current, ActorPtr missile);

};

typedef std::shared_ptr<ShotAction> ShotActionPtr;
typedef std::unique_ptr<ShotAction> ShotActionUPtr;

}
#endif // SHOT_ACTION_H
