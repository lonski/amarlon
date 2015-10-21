#ifndef SKILL_DESCRIPTION
#define SKILL_DESCRIPTION

#include <memory>
#include <description.h>

namespace amarlon {

struct SkillDescription;
typedef std::shared_ptr<SkillDescription> SkillDescriptionPtr;

struct SkillDescription : Description
{
  SkillDescription()
    : id(0)
    , target(0)
    , radius(0)
    , passive(false)
  {}

  int id;
  std::string name;
  int target;
  int radius;
  bool passive;

};

}

#endif // SKILL_DESCRIPTION

