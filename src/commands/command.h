#ifndef COMMAND_H
#define COMMAND_H

#include <libtcod.hpp>
#include <actor.h>
#include <memory>

namespace amarlon {

enum class CommandId
{
  Null,
  Move,
  Open,
  FullScreen,
  Inventory,
  Pick,
  Close,
  Use,
  Help,
  PutInto,
  Look,
  Cast,
  GameMenu,
  Spellbook,
  End
};

class Command;
typedef std::shared_ptr<Command> CommandPtr;

/**
 * @brief Command represent an user's input.
 */
class Command
{
public:
  Command() = default;
  virtual ~Command() {}
  static CommandPtr create(CommandId cmd);

  /**
   * @return True if given key is matching the command
   */
  virtual bool accept(TCOD_key_t &key) = 0;

  /**
   * @return The amount of turns the command execution took.
   */
  virtual int execute() = 0;

};

}

#endif // COMMAND_H
