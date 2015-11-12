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
  virtual int update(Ai* ai) = 0;

};

}

#endif // FSM_STATE_H
