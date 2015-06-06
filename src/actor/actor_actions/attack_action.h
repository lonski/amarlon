#ifndef ATTACK_ACTION_H
#define ATTACK_ACTION_H

#include <memory>
#include <actor_action.h>

namespace amarlon {

class AttackAnimation;
typedef std::shared_ptr<AttackAnimation> AttackAnimationPtr;

class AttackAction : public ActorAction
{
public:
    AttackAction(ActorPtr target);
    virtual ~AttackAction();

    virtual bool run(ActorPtr performer);
    virtual ActorActionUPtr clone();

    virtual int getActionPointCount() const;
    virtual bool isRunning() const;
    virtual void tick();

private:
    ActorPtr _target;
    ActorPtr _performer;
    int _actionPoints;
    int _ticksLeft;
    bool _running;
    AttackAnimationPtr _anim;

    bool perform();
};

typedef std::shared_ptr<AttackAction> AttackActionPtr;
typedef std::unique_ptr<AttackAction> AttackActionUPtr;

}

#endif // ATTACK_ACTION_H
