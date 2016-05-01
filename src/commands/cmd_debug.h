#ifndef CMD_DEBUG_H
#define CMD_DEBUG_H

#include <vector>
#include <command.h>

namespace amarlon {

class CmdDebug : public Command
{
public:
  CmdDebug();
  virtual ~CmdDebug();

  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();

private:
  void inspectActor();
  void inspectTile();
  void advancePlayerLevel();
  void showInfo(ActorPtr a);
  void createItem();
  void toggleInvisibility();
  void generateMagicWeapon();

};

}

#endif // CMD_DEBUG_H
