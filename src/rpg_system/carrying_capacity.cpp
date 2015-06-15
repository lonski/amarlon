#include "carrying_capacity.h"

namespace amarlon {

namespace CarryingCapacity {

  CarryingCapacityData get(int str, Race race)
  {
    return capacityTable[race][str];
  }

}
}
