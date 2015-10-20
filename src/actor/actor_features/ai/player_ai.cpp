#include "player_ai.h"
#include <command_executor.h>

namespace amarlon {

const ActorFeature::Type PlayerAi::featureType = ActorFeature::AI;

PlayerAi::PlayerAi(AiDescriptionPtr /*dsc*/)
  : _cmdExecutor( new CommandExecutor )
{
}

PlayerAi::PlayerAi()
  : PlayerAi(nullptr)
{
}

ActorFeaturePtr PlayerAi::clone()
{
  return ActorFeaturePtr( new PlayerAi(*this) );
}

bool PlayerAi::isEqual(ActorFeaturePtr rhs) const
{
  return std::dynamic_pointer_cast<PlayerAi>(rhs) != nullptr;
}

int PlayerAi::processInput(TCOD_key_t key)
{
  return canOperate() ? _cmdExecutor->execute(key) : 1;
}

}
