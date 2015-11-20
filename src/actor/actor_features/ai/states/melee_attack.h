#ifndef MELEE_ATTACK_H
#define MELEE_ATTACK_H

#include <vector>
#include <memory>
#include <fsm_state.h>

namespace amarlon {

class Ai;
class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

namespace state{

class MeleeAttack : public FSMState
{
public:
  MeleeAttack();

  virtual FSMStateType getType() const;
  virtual int update();
  virtual bool canEnter();
  virtual void onEnter();

private:
  std::vector<ActorPtr> getWeapons();

};

}}

#endif // MELEE_ATTACK_H
