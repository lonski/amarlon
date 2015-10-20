#ifndef AI_DESCRIPTION
#define AI_DESCRIPTION

#include <description.h>
#include <ai_type.h>

namespace amarlon {

struct AiDescription : Description
{
  AiType type;
};

typedef std::shared_ptr<AiDescription> AiDescriptionPtr;

}

#endif // AI_DESCRIPTION

