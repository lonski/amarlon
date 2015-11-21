#ifndef TRAP_DESCRIPTION
#define TRAP_DESCRIPTION

#include <description.h>
#include <experimental/optional>

namespace amarlon {

struct TrapDescription : Description
{
  std::experimental::optional<bool> armed;
  std::experimental::optional<int>  id;
  std::experimental::optional<int>  difficulty;
  std::experimental::optional<bool> detected;
};

typedef std::shared_ptr<TrapDescription> TrapDescriptionPtr;

}

#endif // TRAP_DESCRIPTION

