#ifndef MOVE_TO_TARGET_H
#define MOVE_TO_TARGET_H

#include <fsm_state.h>

namespace amarlon {

class Ai;

namespace state{

class MoveToTarget : public FSMState
{
public:
  MoveToTarget();

  virtual FSMStateType getType() const;
  virtual int update(Ai* ai);

};

}}

#endif // MOVE_TO_TARGET_H
