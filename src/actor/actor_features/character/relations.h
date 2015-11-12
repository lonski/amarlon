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
  Monster,
  NPC,
  Player
};

static std::vector< std::vector<Type> > table = {
  /*         |    Monster | NPC     | Player | */
  /* ------------------------------------------*/
  /* Monster |*/ {Neutral,  Hostile,  Hostile },
  /* NPC     |*/ {Hostile,  Neutral,  Neutral },
  /* Player  |*/ {Hostile,  Neutral,  Ally    }
};

Type get(Team t1, Team t2);

}}

#endif // RELATIONS_H
