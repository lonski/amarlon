#include "module.h"
#include <configuration.h>
#include <utils.h>

namespace amarlon {

Module::Module(const std::string& name)
  : _name(name)
  , _startMap(0)
  , _startX(0)
  , _startY(0)
{
  Configuration cfg;
  if ( cfg.load( getPath() + "info.cfg") )
  {
    _startMap   = fromStr<int>( cfg.get("start_map") );
    _startX     = fromStr<int>( cfg.get("start_x") );
    _startY     = fromStr<int>( cfg.get("start_y") );
    _prettyName = cfg.get("name");
  }
}

std::string Module::getName() const
{
  return _prettyName.empty() ? _name : _prettyName;
}

std::string Module::getPath() const
{
  return "modules/" + _name + "/";
}

int Module::getStartMap() const
{
  return _startMap;
}

int Module::getStartX() const
{
  return _startX;
}

int Module::getStartY() const
{
  return _startY;
}

}
