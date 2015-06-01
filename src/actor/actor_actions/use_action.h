#ifndef USE_ACTION_H
#define USE_ACTION_H

#include <memory>
#include <vector>
#include <actor_action.h>

namespace amarlon {

class UseAction : public ActorAction
{
public:
    UseAction(std::vector<ActorPtr> targets, ActorPtr toUse);
    virtual ~UseAction();

    virtual bool perform(ActorPtr performer);
    virtual ActorActionUPtr clone();

private:
    ActorPtr _performer;
    std::vector<ActorPtr> _targets;
    ActorPtr _toUse;

    void removeUsedItemFromInventory();

};

typedef std::shared_ptr<UseAction> UseActionPtr;
typedef std::unique_ptr<UseAction> UseActionUPtr;

}

#endif // USE_ACTION_H
