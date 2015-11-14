#include "player_controlled.h"
#include <command_executor.h>
#include <ai.h>
#include <engine.h>
#include <key.h>

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
  TCOD_key_t lastKey = Engine::instance().getLastInput();
  if ( ai && lastKey.vk != TCODK_NONE )
  {
    Engine::instance().setLastInput( Key() );
    int r = _cmdExecutor->execute( lastKey );
    return r;
  }
  return 0;
}

}}
