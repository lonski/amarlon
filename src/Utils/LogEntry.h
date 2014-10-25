#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <string>
#include "libtcod.hpp"

namespace amarlon {

struct LogEntry
{
  std::string msg;
  TCODColor color;

  LogEntry(const std::string& m, TCODColor c)
    : msg(m)
    , color(c)
  {}
};

}

#endif // LOGENTRY_H
