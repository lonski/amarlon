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

static inline bool handleDirectionKey(TCOD_key_t &key, int& dx, int& dy)
{
  bool handled = true;

  switch(key.vk)
  {
    case TCODK_DOWN: dy++; break;
    case TCODK_UP: dy--; break;
    case TCODK_LEFT: dx--; break;
    case TCODK_RIGHT: dx++; break;
    case TCODK_KP7: dx--; dy--; break;
    case TCODK_KP9: dx++; dy--; break;
    case TCODK_KP1: dx--; dy++; break;
    case TCODK_KP3: dx++; dy++; break;
    default: handled = false; break;
  }

  return handled;
}

#endif // UTILS_H
