#ifndef TRAP_ID
#define TRAP_ID

#include <string>

namespace amarlon {

enum class TrapId
{
  Null = 0,
  BladeTrap
};

static inline std::string TrapId2Str(TrapId t)
{
  std::string str = "";
  switch ( t )
  {
    case TrapId::BladeTrap: str = "Blade trap"; break;
    default:;
  }
  return str;
}

}

#endif // TRAP_ID

