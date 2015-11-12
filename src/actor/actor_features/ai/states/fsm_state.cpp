#include "fsm_state.h"
#include <move_to_target.h>
#include <idle.h>
#include <melee_attack.h>
#include <player_controlled.h>

namespace amarlon {

FSMState::FSMState()
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
    default:;
  }

  return s;
}

}

