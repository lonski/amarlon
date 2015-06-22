#ifndef AI_FACTORY_H
#define AI_FACTORY_H

#include <memory>
#include <vector>
#include <ai.h>

namespace amarlon{

class AiFactory
{
public:
  AiFactory();
  AiPtr produce(AiDescriptionPtr dsc);

private:
  std::vector< std::shared_ptr<Ai::Creator> > _creators;

};

}

#endif // AI_FACTORY_H
