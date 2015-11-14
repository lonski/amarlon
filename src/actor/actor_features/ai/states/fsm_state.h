#ifndef FSM_STATE_H
#define FSM_STATE_H

#include <memory>
#include <fsm_state_type.h>

namespace amarlon {

class FSMState;
class Ai;
typedef std::shared_ptr<FSMState> FSMStatePtr;

class FSMState
{
public:
  FSMState();
  virtual ~FSMState();

  static FSMStatePtr create(FSMStateType type);

  virtual FSMStateType getType() const = 0;
  virtual int update() = 0;
  virtual bool canEnter() = 0;
  virtual void onEnter() {}
  virtual void onExit() {}
  virtual void setAi(Ai* ai);

protected:
  Ai* _ai;

};

}

#endif // FSM_STATE_H
