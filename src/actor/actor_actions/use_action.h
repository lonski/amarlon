#ifndef USE_ACTION_H
#define USE_ACTION_H

#include <memory>
#include <vector>
#include <actor_action.h>
#include <target.h>

namespace amarlon {

class UseAction : public ActorAction
{
public:
    UseAction(const Target& target, ActorPtr toUse);
    virtual ~UseAction();

    virtual ActorActionResult perform(ActorPtr performer);
    virtual ActorActionUPtr clone();

private:
    ActorPtr _performer;
    Target _target;
    ActorPtr _toUse;

    void removeUsedItemFromInventory();

};

typedef std::shared_ptr<UseAction> UseActionPtr;
typedef std::unique_ptr<UseAction> UseActionUPtr;

}

#endif // USE_ACTION_H
