#ifndef OPENABLE_DESCRIPTION
#define OPENABLE_DESCRIPTION

#include <description.h>

namespace amarlon {

struct OpenableDescription : Description
{
  OpenableDescription()
    : lockId(0)
    , locked(false)
    , scriptId(0)
    , closed(false)
    , lockLevel(0)
  {}

  int lockId;
  bool locked;
  int scriptId;
  bool closed;
  int lockLevel;
};

typedef std::shared_ptr<OpenableDescription> OpenableDescriptionPtr;

}

#endif // OPENABLE_DESCRIPTION

