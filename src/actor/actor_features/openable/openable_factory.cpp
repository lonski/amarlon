#include "openable_factory.h"
#include <openable_container.h>
#include <openable_door.h>

namespace amarlon
{

OpenableFactory::OpenableFactory()
{
  _creators.push_back( std::make_shared<OpenableDoor::Creator>() );
  _creators.push_back( std::make_shared<OpenableContainer::Creator>() );
}

OpenablePtr OpenableFactory::produce(OpenableDescriptionPtr dsc)
{
  OpenablePtr op = nullptr;

  if ( dsc != nullptr )
  {
    for ( auto creator : _creators )
    {
      op = creator->create(dsc);
      if ( op != nullptr ) break;
    }
  }

  return op;
}

}
