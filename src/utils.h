#ifndef UTILS_H
#define UTILS_H

#include "libtcod.hpp"
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

static inline std::string colorToStr(TCODColor color)
{
  std::stringstream ss;
  std::string s;

  ss << std::setfill('0')
     << std::setw(2) << std::hex << (int)color.r
     << std::setw(2) << std::hex << (int)color.g
     << std::setw(2) << std::hex << (int)color.b;

  return ss.str();
}

static inline TCODColor strToColor(const std::string& str)
{
  TCODColor col;
  if (str.size() == 6)
  {
    std::stringstream ss;
    int r(0),g(0),b(0);

    ss << std::hex << str.substr(0,2);
    ss >> r;
    col.r = r;

    ss.clear();

    ss << std::hex << str.substr(2,2);
    ss >> g;
    col.g = g;
    ss.clear();

    ss << std::hex << str.substr(4,2);
    ss >> b;
    col.b = b;

  }
  return col;
}

#endif // UTILS_H
