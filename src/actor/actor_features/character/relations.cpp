#include "relations.h"

namespace amarlon {

namespace relations {

Type get(Team t1, Team t2)
{
  return table[t1][t2];
}

}

}
