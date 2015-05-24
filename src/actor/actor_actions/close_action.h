#ifndef CLOSE_ACTION_H
#define CLOSE_ACTION_H

#include <memory>
#include <actor_action.h>

namespace amarlon {

class CloseAction : public ActorAction
{
public:
  CloseAction(ActorPtr toClose);
  virtual ~CloseAction();

  virtual bool perform(ActorPtr performer);
  virtual ActorActionUPtr clone();

private:
  ActorPtr _toClose;

};

typedef std::shared_ptr<CloseAction> CloseActionPtr;
typedef std::unique_ptr<CloseAction> CloseActionUPtr;

}

#endif // CLOSE_ACTION_H
