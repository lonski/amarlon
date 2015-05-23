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

  virtual bool perform(ActorPtr performer);

private:
  ActorPtr _toOpen;
};

}

#endif // OPEN_ACTION_H
