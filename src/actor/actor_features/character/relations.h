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
  PcHostileNPC = 3
};

static std::vector< std::vector<Type> > table = {
  /*               |    Monster | NPC     | Player |  PcHostileNPC */
  /* --------------------------------------------------------------*/
  /* Monster       |*/ {Neutral,  Hostile,  Hostile, Hostile },
  /* NPC           |*/ {Hostile,  Neutral,  Neutral, Neutral },
  /* Player        |*/ {Hostile,  Neutral,  Ally,    Hostile },
  /* PcHostileNPC  |*/ {Hostile,  Neutral,  Hostile, Ally    },
};

Type get(Team t1, Team t2);

}}

#endif // RELATIONS_H
