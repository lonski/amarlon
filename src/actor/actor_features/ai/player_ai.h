#ifndef PLAYER_AI_H
#define PLAYER_AI_H

#include <memory>
#include <ai.h>
#include <libtcod.hpp>

namespace amarlon {

class CommandExecutor;
class PlayerAi;
typedef std::shared_ptr<CommandExecutor> CommandExecutorPtr;
typedef std::shared_ptr<PlayerAi> PlayerAiPtr;

class PlayerAi : public Ai
{
public:
  const static ActorFeature::Type featureType;
  virtual AiType getAiType() const;

  PlayerAi(AiDescriptionPtr dsc);
  PlayerAi();

  virtual ActorFeaturePtr clone();
  virtual bool isEqual(ActorFeaturePtr rhs) const;

  virtual void update() {}

  /**
   * @brief Processes Player's commands.
   * @return Amount of turns that the processing took.
   */
  virtual int processInput(TCOD_key_t key);

  virtual bool isHostileTo(ActorPtr actor) const;
  virtual bool isAllyOf(ActorPtr actor) const;

private:
  CommandExecutorPtr _cmdExecutor;

};

}

#endif // PLAYER_AI_H
