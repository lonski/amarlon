#ifndef DESTROYABLE_DESCRIPTION
#define DESTROYABLE_DESCRIPTION

#include <vector>
#include <description.h>

namespace amarlon {

struct DestroyableDescription : Description
{
  DestroyableDescription()
  {}

  //std::vector<DropRule> dropRules;
};

typedef std::shared_ptr<DestroyableDescription> DestroyableDescriptionPtr;

}

#endif // DESTROYABLE_DESCRIPTION

