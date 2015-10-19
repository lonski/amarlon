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
    , detected(false)
  {}

  bool armed;
  int id;
  int difficulty;
  bool detected;
};

typedef std::shared_ptr<TrapDescription> TrapDescriptionPtr;

}

#endif // TRAP_DESCRIPTION

