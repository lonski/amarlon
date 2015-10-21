#ifndef MODIFIER
#define MODIFIER

#include <modifier_type.h>

namespace amarlon {

class Modifier
{
public:
  Modifier(int val = 0, ModifierType t = ModifierType())
    : Value(val)
    , Type(t)
  {}

  bool operator==(const Modifier& rhs)
  {
    return Value == rhs.Value && Type == rhs.Type;
  }

  int Value;
  ModifierType Type;
};

}

#endif // MODIFIER

