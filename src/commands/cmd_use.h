#ifndef CMDUSE_H
#define CMDUSE_H

#include <vector>
#include <command.h>

namespace amarlon {

class Scroll;
typedef std::shared_ptr<Scroll> ScrollPtr;

class CmdUse : public Command
{
public:
  CmdUse();

  virtual bool accept(const TCOD_key_t& key);
  virtual int execute();
  
private:
  ActorPtr acquireItemToUse();
  std::vector<ActorPtr> getUsableItems();
  int useItem(ActorPtr item);
  bool knowSpell(SpellPtr spell);
  int transcribeScroll(ScrollPtr scroll);

};

}

#endif // CMDUSE_H
