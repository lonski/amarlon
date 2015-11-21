#ifndef AI_DESCRIPTION
#define AI_DESCRIPTION

#include <description.h>
#include <ai_type.h>
#include <experimental/optional>

namespace amarlon {

struct AiDescription : Description
{
  std::experimental::optional<AiType> type;
  std::experimental::optional<int> script;
};

typedef std::shared_ptr<AiDescription> AiDescriptionPtr;

}

#endif // AI_DESCRIPTION

