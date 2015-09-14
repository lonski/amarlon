#ifndef CMS_CAST_H
#define CMS_CAST_H

#include <vector>
#include <command.h>

namespace amarlon {

class Spell;
typedef std::shared_ptr<Spell> SpellPtr;

class CmdCast : public Command
{
public:
  CmdCast();

  virtual bool accept(TCOD_key_t &key);
  virtual int execute();

private:
  SpellPtr getSpell();

};

}

#endif // CMS_CAST_H
