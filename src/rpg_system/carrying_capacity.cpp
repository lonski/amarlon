#include "carrying_capacity.h"

namespace amarlon {

namespace CarryingCapacity {

  Data get(int str, Race race)
  {
    return capacityTable[race][str];
  }

}
}

