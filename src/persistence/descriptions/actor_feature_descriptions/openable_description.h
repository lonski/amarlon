#ifndef OPENABLE_DESCRIPTION
#define OPENABLE_DESCRIPTION

#include <description.h>
#include <experimental/optional>

namespace amarlon {

struct OpenableState
{
  OpenableState()
    : symbol('#')
    , transparent(false)
    , blocks(false)
  {}

  unsigned char symbol;
  bool transparent;
  bool blocks;

  bool operator==(const OpenableState& rhs) const
  {
    return symbol == rhs.symbol && transparent == rhs.transparent
        && blocks == rhs.blocks;
  }

  bool operator!=(const OpenableState& rhs) const
  {
    return !(*this == rhs);
  }
};

struct OpenableDescription : Description
{
  std::experimental::optional<int>  lockId;
  std::experimental::optional<bool> locked;
  std::experimental::optional<int>  scriptId;
  std::experimental::optional<bool> closed;
  std::experimental::optional<int>  lockLevel;
  std::experimental::optional<OpenableState> openedState;
  std::experimental::optional<OpenableState> closedState;

  bool any()
  {
    return lockId || locked || scriptId || closed || lockLevel;
  }
};

typedef std::shared_ptr<OpenableDescription> OpenableDescriptionPtr;

}

#endif // OPENABLE_DESCRIPTION

