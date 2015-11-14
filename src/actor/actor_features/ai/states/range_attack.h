#ifndef RANGE_ATTACK_H
#define RANGE_ATTACK_H

#include <fsm_state.h>

namespace amarlon {

class Ai;

namespace state{

class RangeAttack : public FSMState
{
public:
  RangeAttack();

  virtual FSMStateType getType() const;
  virtual int update(Ai* ai);

};

}}

#endif // RANGE_ATTACK_H
