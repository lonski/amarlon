#include "fsm.h"
#include <fsm_state.h>

namespace amarlon {

FSM::FSM()
{
  for ( auto s : FSMStateType() )
    _states[s] = FSMState::create(s);

  _currentState = _states[FSMStateType::IDLE];
}

int amarlon::FSM::update(Ai* ai)
{
  return _currentState ? _currentState->update(ai) : 0;
}

FSMStatePtr FSM::getCurrentState() const
{
  return _currentState;
}

void FSM::addState(FSMStatePtr state)
{
  _states[ state->getType() ] = state;
}

bool FSM::changeState(FSMStateType newState)
{
  auto it = _states.find( newState );
  if ( it != _states.end() )
  {
    _currentState = it->second;
    return true;
  }
  return false;
}

}

