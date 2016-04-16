#include "module.h"

namespace amarlon {

Module::Module(const std::string& name)
  : _name(name)
{
}

std::string Module::getName() const
{
  return _name;
}

std::string Module::getPath() const
{
  return "modules/" + getName() + "/";
}

}
