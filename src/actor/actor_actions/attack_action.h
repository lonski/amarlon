#ifndef ATTACK_ACTION_H
#define ATTACK_ACTION_H

#include <actor_action.h>

namespace amarlon {

class AttackAction : public ActorAction
{
public:
    AttackAction(ActorPtr target);
    virtual ~AttackAction();

    virtual bool perform(ActorPtr performer);

private:
    ActorPtr _target;
    ActorPtr _performer;
};

}

#endif // ATTACK_ACTION_H
