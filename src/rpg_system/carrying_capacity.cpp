#include "carrying_capacity.h"

namespace amarlon {

namespace CarryingCapacity {

  Data get(int str, RaceType race)
  {
    return capacityTable[race][str];
  }

}
}

