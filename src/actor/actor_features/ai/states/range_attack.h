#ifndef RANGE_ATTACK_H
#define RANGE_ATTACK_H

#include <vector>
#include <memory>
#include <fsm_state.h>

namespace amarlon {

class Ai;
class Actor;
class Pickable;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<Pickable> PickablePtr;

namespace state{

class RangeAttack : public FSMState
{
public:
  RangeAttack();

  virtual FSMStateType getType() const;
  virtual int update();
  virtual bool canEnter();
  virtual void onEnter();

private:
  std::vector<ActorPtr> getWeapons();
  std::vector<ActorPtr> getAmunition(PickablePtr weapon);
  void chooseWeapon();
  void equip();
  bool isOutOfAmmo();

  ActorPtr _weapon;
  ActorPtr _amunition;

};

}}

#endif // RANGE_ATTACK_H
