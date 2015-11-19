#include "carrying_capacity.h"

namespace amarlon {

namespace CarryingCapacity {

  Data get(int str, RaceType race)
  {
    auto it = capacityTable.find(race);
    if ( it == capacityTable.end() ) race = RaceType::Human;
    return capacityTable[race][str];
  }

}
}

