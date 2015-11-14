#ifndef PLAYER_CONTROLLED_H
#define PLAYER_CONTROLLED_H

#include <fsm_state.h>

namespace amarlon {

class Ai;
class CommandExecutor;
typedef std::shared_ptr<CommandExecutor> CommandExecutorPtr;

namespace state{

class PlayerControlled : public FSMState
{
public:
  PlayerControlled();

  virtual FSMStateType getType() const;
  virtual int update();
  virtual bool canEnter();

private:
  CommandExecutorPtr _cmdExecutor;

};

}}

#endif // PLAYER_CONTROLLED_H
