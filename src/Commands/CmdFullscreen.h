#ifndef CMDFULLSCREEN_H
#define CMDFULLSCREEN_H

#include "command.h"

class CmdFullscreen : public Command
{
public:
  CmdFullscreen();
  bool accept(TCOD_key_t &key, Actor*, Map*);

};

#endif // CMDFULLSCREEN_H
