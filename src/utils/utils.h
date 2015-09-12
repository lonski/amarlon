#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <memory>
#include "libtcod.hpp"
#include <target.h>

namespace amarlon {

class Actor;
typedef std::shared_ptr<Actor> ActorPtr;

std::vector<std::string> explode(const std::string& str, char ch);
std::string tolowers(const std::string& str);
std::string colorToStr(TCODColor color, bool braces = false);
TCODColor strToColor(const std::string& str);
bool handleDirectionKey(TCOD_key_t &key, int& dx, int& dy);
std::string getItemNameAndAmount(ActorPtr a);
float calculateDistance(int ox, int oy, int tx, int ty);
TCODPath *calculatePath(Target start, Target end );

template<typename T>
static T fromStr(const std::string& s)
{
  std::istringstream is(s);
  T t;
  is >> t;
  return t;
}

template<typename T>
static std::string toStr(const T& t)
{
  std::ostringstream os;
  os << t;
  return os.str();
}

template<typename T>
std::string to_stringp(T t, int prec = 1)
{
  std::stringstream ss;
  ss << std::setprecision(prec) << t;
  return ss.str();
}

template<typename T>
void setBit(T& var, int n, bool value)
{
  var ^= (-value ^ var) & (1 << n);
}

template<typename T>
bool isBitSet(T& var, int n)
{
  return (var >> n) & 1;
}

}
#endif // UTILS_H
