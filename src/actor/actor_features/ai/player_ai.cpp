#include "player_ai.h"
#include <command_executor.h>
#include <actor.h>

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

AiType PlayerAi::getAiType() const
{
  return AiType::PlayerAi;
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

bool PlayerAi::isHostileTo(ActorPtr actor) const
{
  if ( actor )
  {
    AiPtr ai = actor->getFeature<Ai>();
    //Hostile to monsters
    return ai && ai->getAiType() == AiType::MonsterAi;
  }
  return false;
}

bool PlayerAi::isAllyOf(ActorPtr actor) const
{
  if ( actor )
  {
    AiPtr ai = actor->getFeature<Ai>();
    //Allied with player only
    return ai && ai->getAiType() == AiType::PlayerAi;
  }
  return false;
}

}
