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

private:
  ActorPtr _toClose;

};

}

#endif // CLOSE_ACTION_H
