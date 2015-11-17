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
#include <point.h>

namespace amarlon {

class DirectPath;
class Actor;
typedef std::shared_ptr<Actor> ActorPtr;
typedef std::shared_ptr<DirectPath> DirectPathPtr;

std::vector<std::string> explode(const std::string& str, char ch);
std::string tolowers(const std::string& str);
std::string colorToStr(TCODColor color, bool braces = false);
TCODColor strToColor(const std::string& str);
bool handleDirectionKey(const TCOD_key_t& key, int& dx, int& dy);
std::string getItemNameAndAmount(ActorPtr a);
float calculateDistance(int ox, int oy, int tx, int ty);
float calculateDistance(ActorPtr a1, ActorPtr a2);
TCODPath *calculatePath(Target start, Target end );
DirectPathPtr calculateDirectPath(Target start, Target end);
float tangens(const Point& p1, const Point& p2);

static inline std::string &ltrim(std::string &s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
}

static inline std::string &rtrim(std::string &s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
        return s;
}

static inline std::string &trim(std::string &s) {
        return ltrim(rtrim(s));
}

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

struct MinMax
{
  MinMax(int min_ = 0, int max_ = 0)
    : min(min_)
    , max(max_)
  {}

  void merge(const MinMax& rhs)
  {
    min = std::max(min, rhs.min);
    max = std::min(max, rhs.max);
  }

  bool allow(int val) const
  {
    return val >= min && val <= max;
  }

  int min;
  int max;
};

}
#endif // UTILS_H
