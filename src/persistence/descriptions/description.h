#ifndef DESCRIPTION
#define DESCRIPTION

#include <memory>

namespace amarlon {

struct Description;
typedef std::shared_ptr<Description> DescriptionPtr;

struct Description
{
  virtual ~Description() {}
};

}

#endif // DESCRIPTION

