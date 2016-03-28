#ifndef ATTACK_ACTION_H
#define ATTACK_ACTION_H

#include <memory>
#include <actor_action.h>

namespace amarlon {

class AttackAction : public ActorAction
{
public:
    AttackAction(ActorPtr target);
    virtual ~AttackAction();

    virtual ActorActionResult perform(ActorPtr performer);
    virtual ActorActionUPtr clone();

private:
    ActorPtr _target;
    ActorPtr _performer;
};

typedef std::shared_ptr<AttackAction> AttackActionPtr;
typedef std::unique_ptr<AttackAction> AttackActionUPtr;

}

#endif // ATTACK_ACTION_H
