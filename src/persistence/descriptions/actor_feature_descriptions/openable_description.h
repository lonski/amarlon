#ifndef OPENABLE_DESCRIPTION
#define OPENABLE_DESCRIPTION

#include <description.h>
#include <experimental/optional>

namespace amarlon {

struct OpenableDescription : Description
{
  std::experimental::optional<int>  lockId;
  std::experimental::optional<bool> locked;
  std::experimental::optional<int>  scriptId;
  std::experimental::optional<bool> closed;
  std::experimental::optional<int>  lockLevel;

  bool any()
  {
    return lockId || locked || scriptId || closed || lockLevel;
  }
};

typedef std::shared_ptr<OpenableDescription> OpenableDescriptionPtr;

}

#endif // OPENABLE_DESCRIPTION

