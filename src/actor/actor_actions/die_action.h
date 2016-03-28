#ifndef DIE_ACTION_H
#define DIE_ACTION_H

#include <memory>
#include <actor_action.h>

namespace amarlon
{

class DieAction : public ActorAction
{
public:
  DieAction();
  ~DieAction();

  virtual ActorActionResult perform(ActorPtr performer);
  virtual ActorActionUPtr clone();

private:
  ActorPtr _performer;

  void dropOnGround(ActorPtr item);
  void dropItemsFromBody();

};

}

#endif // DIE_ACTION_H
