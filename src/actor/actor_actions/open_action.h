#ifndef OPEN_ACTION_H
#define OPEN_ACTION_H

#include <memory>
#include <actor_action.h>

namespace amarlon {

class OpenAction : public ActorAction
{
public:
  OpenAction(ActorPtr toOpen);
  virtual ~OpenAction();

  virtual ActorActionResult perform(ActorPtr performer);
  virtual ActorActionUPtr clone();

private:
  ActorPtr _toOpen;
};

typedef std::shared_ptr<OpenAction> OpenActionPtr;
typedef std::unique_ptr<OpenAction> OpenActionUPtr;

}

#endif // OPEN_ACTION_H
