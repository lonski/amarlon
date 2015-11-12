#include "player_controlled.h"
#include <command_executor.h>
#include <ai.h>
#include <engine.h>

namespace amarlon {

namespace state{

PlayerControlled::PlayerControlled()
  : _cmdExecutor( new CommandExecutor )
{

}

FSMStateType PlayerControlled::getType() const
{
  return FSMStateType::PLAYER_CONTROLLED;
}

int PlayerControlled::update(Ai* ai)
{
  if ( ai )
  {
    return _cmdExecutor->execute( Engine::instance().getLastInput() );
  }
  return 0;
}

}}
