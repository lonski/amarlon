#ifndef MODIFIER
#define MODIFIER

#include <modifier_type.h>
#include <utils.h>

namespace amarlon {

class Modifier
{
public:
  Modifier(int val = 0, ModifierType t = ModifierType())
    : Value(val)
    , Type(t)
  {}

  Modifier(const std::string& str)
  {
    fromString(str);
  }

  bool operator==(const Modifier& rhs)
  {
    return Value == rhs.Value && Type == rhs.Type;
  }

  std::string toString() const
  {
    std::string str;
    str += std::to_string(Value) + "@";
    str += Type.toString();
    return str;
  }

  void fromString(const std::string& str)
  {
    Value = 0;
    Type = ModifierType();

    std::vector<std::string> vals = explode(str,'@');
    if ( vals.size() > 0 ) Value = fromStr<int>(vals[0]);
    if ( vals.size() > 1 ) Type.fromString(vals[1]);
  }

  int Value;
  ModifierType Type;
};

}

#endif // MODIFIER

