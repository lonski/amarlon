#ifndef AI_DESCRIPTION
#define AI_DESCRIPTION

#include <description.h>

namespace amarlon {


struct AiDescription : Description
{
};

struct MonsterAiDescription : AiDescription
{
};

typedef std::shared_ptr<AiDescription> AiDescriptionPtr;
typedef std::shared_ptr<MonsterAiDescription> MonsterAiDescriptionPtr;

}

#endif // AI_DESCRIPTION

