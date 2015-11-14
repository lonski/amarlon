#include "fsm_state.h"
#include <move_to_target.h>
#include <idle.h>
#include <melee_attack.h>
#include <player_controlled.h>
#include <range_attack.h>

namespace amarlon {

FSMState::FSMState()
  : _ai(nullptr)
{
}

FSMState::~FSMState()
{
}

FSMStatePtr FSMState::create(FSMStateType type)
{
  FSMStatePtr s;

  switch( type )
  {
    case FSMStateType::MOVE_TO_TARGET: s.reset( new state::MoveToTarget ); break;
    case FSMStateType::IDLE: s.reset( new state::Idle ); break;
    case FSMStateType::MELEE_ATTACK: s.reset( new state::MeleeAttack ); break;
    case FSMStateType::PLAYER_CONTROLLED: s.reset( new state::PlayerControlled ); break;
    case FSMStateType::ATTACK_RANGE: s.reset( new state::RangeAttack ); break;
    default:;
  }

  return s;
}

void FSMState::setAi(Ai *ai)
{
  _ai = ai;
}

}

