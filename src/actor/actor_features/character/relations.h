#ifndef RELATIONS_H
#define RELATIONS_H

#include <vector>

namespace amarlon { namespace relations {

enum Type
{
  Hostile,
  Ally,
  Neutral
};

enum Team
{
  Monster      = 0,
  NPC          = 1,
  Player       = 2,
  PcHostileNPC = 3,
  Animals      = 4
};

static std::vector< std::vector<Type> > table = {
  /*               |    Monster | NPC     | Player |  PcHostileNPC | Animals */
  /* ------------------------------------------------------------------------*/
  /* Monster       |*/ {Neutral,  Neutral,  Hostile, Neutral,        Neutral },
  /* NPC           |*/ {Neutral,  Neutral,  Neutral, Neutral,        Neutral },
  /* Player        |*/ {Hostile,  Neutral,  Ally,    Hostile,        Neutral },
  /* PcHostileNPC  |*/ {Neutral,  Neutral,  Hostile, Ally,           Neutral },
  /* Animals       |*/ {Neutral,  Neutral,  Neutral, Neutral,        Neutral },
};

Type get(Team t1, Team t2);

}}

#endif // RELATIONS_H
