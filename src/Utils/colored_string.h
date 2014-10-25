#ifndef COLORED_STRING_H
#define COLORED_STRING_H

#include <string>
#include <libtcod.hpp>

namespace amarlon {

struct ColoredString
{
  ColoredString(std::string s, TCODColor c)
    : str(s)
    , color(c)
  {}

  std::string str;
  TCODColor color;
};

}

#endif // COLORED_STRING_H
