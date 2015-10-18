#ifndef TRAP_DESCRIPTION
#define TRAP_DESCRIPTION

#include <description.h>

namespace amarlon {

struct TrapDescription : Description
{
  TrapDescription()
    : armed(true)
    , id(0)
    , difficulty(0)
  {}

  bool armed;
  int id;
  int difficulty;
};

typedef std::shared_ptr<TrapDescription> TrapDescriptionPtr;

}

#endif // TRAP_DESCRIPTION

