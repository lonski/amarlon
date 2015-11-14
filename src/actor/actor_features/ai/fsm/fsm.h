#ifndef FSM_H
#define FSM_H

#include <memory>
#include <map>
#include <fsm_state_type.h>

namespace amarlon {

class FSMState;
class Ai;
typedef std::shared_ptr<FSMState> FSMStatePtr;

class FSM
{
public:
  FSM(Ai *ai);

  int update();

  FSMStatePtr getCurrentState() const;
  void addState(FSMStatePtr state);
  bool changeState(FSMStateType newState);

private:
  Ai* _ai;
  FSMStatePtr _currentState;
  std::map<FSMStateType, FSMStatePtr> _states;

};

typedef std::shared_ptr<FSM> FSMPtr;

}

#endif // FSM_H
