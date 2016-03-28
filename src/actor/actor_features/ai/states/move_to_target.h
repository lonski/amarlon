#ifndef MOVE_TO_TARGET_H
#define MOVE_TO_TARGET_H

#include <fsm_state.h>
#include <libtcod.hpp>

namespace amarlon {

class Ai;

namespace state{

class MoveToTarget : public FSMState
{
public:
  MoveToTarget();

  virtual FSMStateType getType() const;
  virtual int update();
  virtual bool canEnter();

private:
  std::unique_ptr<TCODPath> _path;

};

}}

#endif // MOVE_TO_TARGET_H
