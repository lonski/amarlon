#include "ai_factory.h"
#include <monster_ai.h>

namespace amarlon
{

AiFactory::AiFactory()
{
  _creators.push_back( std::make_shared<MonsterAi::Creator>() );
}

AiPtr AiFactory::produce(AiDescriptionPtr dsc)
{
  AiPtr ai = nullptr;

  if ( dsc != nullptr )
  {
    for ( auto creator : _creators )
    {
      ai = creator->create(dsc);
      if ( ai != nullptr ) break;
    }
  }

  return ai;
}

}
