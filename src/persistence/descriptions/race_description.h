#ifndef RACE_DESCRIPTION
#define RACE_DESCRIPTION

#include <description.h>
#include <vector>
#include <utils.h>

namespace amarlon {

struct RaceDescription
{
  int id;
  std::string name;
  std::string description;
  bool playable;
  std::vector<int> possibleClasses;
  std::vector< std::pair<int,int> > skills;
  std::vector< std::pair<int, MinMax> > abilityScoreRestrictions;
};

typedef std::shared_ptr<RaceDescription> RaceDescriptionPtr;

}

#endif // RACE_DESCRIPTION

