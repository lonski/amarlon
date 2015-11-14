#ifndef MELEE_ATTACK_H
#define MELEE_ATTACK_H

#include <fsm_state.h>

namespace amarlon {

class Ai;

namespace state{

class MeleeAttack : public FSMState
{
public:
  MeleeAttack();

  virtual FSMStateType getType() const;
  virtual int update();
  virtual bool canEnter();

};

}}

#endif // MELEE_ATTACK_H
