#ifndef AI_DESCRIPTION
#define AI_DESCRIPTION

#include <description.h>
#include <ai_type.h>

namespace amarlon {

struct AiDescription : Description
{
  AiDescription()
    : type(AiType::Null)
    , script(0)
  {}

  AiType type;
  int script;
};

typedef std::shared_ptr<AiDescription> AiDescriptionPtr;

}

#endif // AI_DESCRIPTION

