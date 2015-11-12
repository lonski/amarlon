#ifndef IDLE_H
#define IDLE_H

#include <fsm_state.h>

namespace amarlon {

class Ai;

namespace state{

class Idle : public FSMState
{
public:
  Idle();

  virtual FSMStateType getType() const;
  virtual int update(Ai* ai);

};

}}

#endif // IDLE_H
