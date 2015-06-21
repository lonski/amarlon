#ifndef OPENABLE_FACTORY_H
#define OPENABLE_FACTORY_H

#include <memory>
#include <vector>
#include <openable.h>

namespace amarlon{

class OpenableFactory
{
public:
  OpenableFactory();
  OpenablePtr produce(OpenableDescriptionPtr dsc);

private:
  std::vector< std::shared_ptr<Openable::Creator> > _creators;

};

}

#endif // OPENABLE_FACTORY_H
