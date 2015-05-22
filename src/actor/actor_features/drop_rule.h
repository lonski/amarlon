#ifndef DROP_RULE
#define DROP_RULE

#include <stdint.h>
#include <actor_type.h>

namespace amarlon {

struct DropRule
{
  ActorType dropActorId;
  int amountMin;
  int amountMax;
  float chance;
};

inline bool operator==(const DropRule& lhs, const DropRule& rhs)
{
  return (rhs.dropActorId == lhs.dropActorId) &&
         (rhs.amountMin == lhs.amountMin) &&
         (rhs.amountMax == lhs.amountMax) &&
         (rhs.chance == lhs.chance);
}

}

#endif // DROP_RULE

